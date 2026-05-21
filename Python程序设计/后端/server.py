from fastapi import FastAPI, HTTPException
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel
from transformers import BertTokenizer, BertForSequenceClassification
import torch
from sqlalchemy.orm import Session
from fastapi import Depends, Header
from database import SessionLocal
from models import User
from utils import hash_password, verify_password, generate_api_key
from fastapi import Request

# 加载模型和分词器
MODEL_PATH = "./text_classification_model"
tokenizer = BertTokenizer.from_pretrained(MODEL_PATH)
model = BertForSequenceClassification.from_pretrained(MODEL_PATH)
model.eval()

AD_MODEL_PATH = "./ad_classification_model"
ad_tokenizer = BertTokenizer.from_pretrained(AD_MODEL_PATH)
ad_model = BertForSequenceClassification.from_pretrained(AD_MODEL_PATH)
ad_model.eval()

PORN_MODEL_PATH = "./porn_classification_model"
porn_tokenizer = BertTokenizer.from_pretrained(PORN_MODEL_PATH)
porn_model = BertForSequenceClassification.from_pretrained(PORN_MODEL_PATH)
porn_model.eval()

FRAUD_MODEL_PATH = "./fraud_classification_model"
fraud_tokenizer = BertTokenizer.from_pretrained(FRAUD_MODEL_PATH)
fraud_model = BertForSequenceClassification.from_pretrained(FRAUD_MODEL_PATH)
fraud_model.eval()

ALLOWED_ORIGINS = ["https://localhost:5173"]

# 注册Pydantic模型
class RegisterRequest(BaseModel):
    username: str
    password: str

class LoginRequest(BaseModel):
    username: str
    password: str

# 依赖：数据库会话
def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()

# 创建 FastAPI 应用
app = FastAPI()
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"]
)

# 请求格式
class TextRequest(BaseModel):
    texts: list[str]

@app.post("/register")
def register(request: RegisterRequest, db: Session = Depends(get_db)):
    if db.query(User).filter_by(username=request.username).first():
        raise HTTPException(status_code=400, detail="Username already exists")
    new_user = User(
        username=request.username,
        password_hash=hash_password(request.password),
        api_key=generate_api_key()
    )
    db.add(new_user)
    db.commit()
    db.refresh(new_user)
    return {"message": "User registered successfully", "api_key": new_user.api_key}

@app.post("/login")
def login(request: LoginRequest, db: Session = Depends(get_db)):
    user = db.query(User).filter_by(username=request.username).first()
    if not user or not verify_password(request.password, user.password_hash):
        raise HTTPException(status_code=401, detail="Invalid username or password")
    return {"api_key": user.api_key}

# 推理函数
@app.post("/predict")
def predict(
    request_data: TextRequest,
    request: Request,
    api_key: str = Header(...),  # 从Header获取 API Key
    db: Session = Depends(get_db)
):
    origin = request.headers.get("origin") or request.headers.get("referer", "")

    # 判断是否来自允许免 API Key 的网页
    is_allowed_origin = any(allowed in origin for allowed in ALLOWED_ORIGINS)

    if not is_allowed_origin:
        # 非允许网页，必须提供有效 API Key
        if not api_key:
            raise HTTPException(status_code=401, detail="API Key required")
        user = db.query(User).filter_by(api_key=api_key).first()
        if not user:
            raise HTTPException(status_code=401, detail="Invalid API Key")
    
    try:
        texts = request_data.texts
        encodings = tokenizer(
            texts, truncation=True, padding=True, max_length=128, return_tensors="pt"
        )
        with torch.no_grad():
            aggressive_outputs = model(
                input_ids=encodings["input_ids"],
                attention_mask=encodings["attention_mask"]
            )
            aggressive_probs = torch.softmax(aggressive_outputs.logits, dim=1)
            aggressive_predictions = torch.argmax(aggressive_probs, dim=1).tolist()

            ad_outputs = ad_model(
                input_ids=encodings["input_ids"],
                attention_mask=encodings["attention_mask"]
            )
            ad_probs = torch.softmax(ad_outputs.logits, dim=1)
            ad_predictions = torch.argmax(ad_probs, dim=1).tolist()

            porn_outputs = porn_model(
                input_ids=encodings["input_ids"],
                attention_mask=encodings["attention_mask"]
            )
            porn_probs = torch.softmax(porn_outputs.logits, dim=1)
            porn_predictions = torch.argmax(porn_probs, dim=1).tolist()

            fraud_outputs = fraud_model(
                input_ids=encodings["input_ids"],
                attention_mask=encodings["attention_mask"]
            )
            fraud_probs = torch.softmax(fraud_outputs.logits, dim=1)
            fraud_predictions = torch.argmax(fraud_probs, dim=1).tolist()
        return {
                "aggressive":{
                    "predictions": aggressive_predictions,
                    "probabilities": aggressive_probs.tolist()
                },
                "ad":{
                    "predictions": ad_predictions,
                    "probabilities": ad_probs.tolist()
                },
                "porn":{
                    "predictions": porn_predictions,
                    "probabilities": porn_probs.tolist()
                },
                "fraud":{
                    "predictions": fraud_predictions,
                    "probabilities": fraud_probs.tolist()
                }
            }
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))