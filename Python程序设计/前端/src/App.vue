<template>
  <div class="app-container">
    <el-container>
      <el-header>
        <el-menu :default-active="activeIndex" mode="horizontal" @select="handleSelect">
          <el-menu-item index="1">在线演示</el-menu-item>
          <el-menu-item index="2">获取API key</el-menu-item>
          <div class="user-buttons">
            <el-button v-if="!isLoggedIn" @click="showLoginDialog">登录</el-button>
            <el-button v-if="!isLoggedIn" type="primary" @click="showRegisterDialog">注册</el-button>
            <el-button v-if="isLoggedIn" @click="logout">退出登录</el-button>
          </div>
        </el-menu>
      </el-header>

      <el-main>
        <div v-if="activeIndex === '1'">
          <DetectionForm @show-result="showResult" />
        </div>
        <div v-else-if="activeIndex === '2'" class="api-key-section">
          <h2>您的API Key</h2>
          <el-input v-model="apiKey" readonly class="api-key-input" placeholder="您尚未登录，暂无可用的API Key">
            <template #append>
              <el-button @click="copyApiKey">复制</el-button>
            </template>
          </el-input>
          <p class="api-key-tip">请妥善保管您的API Key，不要泄露给他人</p>
          <el-card>
            <template #header>
              HTTP 调用示例
            </template>
            <el-input readonly type="textarea" :rows="10" placeholder="HTTP调用示例" v-model="httpExample">
            </el-input>
            <el-text>
              返回示例
            </el-text>
            <el-input readonly type="textarea" :rows="10" placeholder="HTTP调用示例" v-model="responseExample">
            </el-input>
          </el-card>
        </div>
      </el-main>
    </el-container>

    <ResultChart v-show="resultDialogVisible" :visible="resultDialogVisible" :result-data="resultData"
      @close="resultDialogVisible = false" />

    <LoginDialog v-if="loginDialogVisible" :visible="loginDialogVisible" @success="handleLoginSuccess"
      @close="loginDialogVisible = false" />

    <RegisterDialog v-if="registerDialogVisible" :visible="registerDialogVisible" @success="handleRegisterSuccess"
      @close="registerDialogVisible = false" />
  </div>
</template>

<script>
import { ref } from 'vue'
import DetectionForm from './components/DetectionForm.vue'
import ResultChart from './components/ResultChart.vue'
import LoginDialog from './components/LoginDialog.vue'
import RegisterDialog from './components/RegisterDialog.vue'
import { ElMessage } from 'element-plus'

export default {
  components: {
    DetectionForm,
    ResultChart,
    LoginDialog,
    RegisterDialog
  },
  setup() {
    const activeIndex = ref('1')
    const isLoggedIn = ref(!!localStorage.getItem('api_key'))
    const resultDialogVisible = ref(false)
    const loginDialogVisible = ref(false)
    const registerDialogVisible = ref(false)
    const resultData = ref(null)
    const apiKey = ref(localStorage.getItem('api_key') || '')
    const httpExample = ref(`curl --location --request POST 'http://localhost:8000/predict' \\
--header 'Content-Type: application/json' \\
--header 'api-key: abcd1234567890' \\
--data-raw '{
  "texts": [
    "这是一段测试文本"
  ]
}'`)
    const responseExample = ref(`{
    "aggressive": {
      "predictions": [
        0
      ],
      "probabilities": [
        [
          0.9941962957382202,
          0.0058037154376506805
        ]
      ]
    },
      "ad": {
      "predictions": [
        1
      ],
      "probabilities": [
        [
          0.031999047845602036,
          0.9680009484291077
        ]
      ]
    },
      "porn": {
      "predictions": [
        0
      ],
      "probabilities": [
        [
          0.9739245772361755,
          0.026075392961502075
        ]
      ]
    },
      "fraud": {
      "predictions": [
        0
      ],
      "probabilities": [
        [
          0.9948857426643372,
          0.005114221479743719
        ]
      ]
    }
} `)

    const handleSelect = (index) => {
      activeIndex.value = index
      if (index === '2' && !isLoggedIn.value) {
        showLoginDialog()
      }
    }

    const showResult = (data) => {
      resultData.value = data
      resultDialogVisible.value = true
    }

    const showLoginDialog = () => {
      loginDialogVisible.value = true
    }

    const showRegisterDialog = () => {
      registerDialogVisible.value = true
    }

    const handleLoginSuccess = (key) => {
      isLoggedIn.value = true
      apiKey.value = key
      localStorage.setItem('api_key', key)
      loginDialogVisible.value = false
      activeIndex.value = '2' // 登录成功后跳转到API Key页面
    }

    const handleRegisterSuccess = (key) => {
      isLoggedIn.value = true
      apiKey.value = key
      localStorage.setItem('api_key', key)
      registerDialogVisible.value = false
      activeIndex.value = '2' // 注册成功后跳转到API Key页面
    }

    const logout = () => {
      isLoggedIn.value = false
      apiKey.value = ''
      localStorage.removeItem('api_key')
      activeIndex.value = '1' // 退出登录后回到首页
    }

    const copyApiKey = () => {
      navigator.clipboard.writeText(apiKey.value)
      ElMessage.success('已复制!')
    }

    return {
      activeIndex,
      isLoggedIn,
      resultDialogVisible,
      loginDialogVisible,
      registerDialogVisible,
      resultData,
      apiKey,
      handleSelect,
      showResult,
      showLoginDialog,
      showRegisterDialog,
      handleLoginSuccess,
      handleRegisterSuccess,
      logout,
      copyApiKey,
      httpExample,
      responseExample
    }
  }
}
</script>

<style>
.app-container {
  height: 100vh;
}

.el-header {
  padding: 0;
  /* background-color: #fff; */
  border-bottom: 1px solid #e6e6e6;
}

.el-menu {
  display: flex;
  justify-content: space-between;
}

.user-buttons {
  display: flex;
  align-items: center;
  padding-right: 20px;
}

.api-key-section {
  text-align: center;
  margin-top: 100px;
}
</style>