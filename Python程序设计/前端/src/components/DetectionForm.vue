<template>
    <div class="detection-container">
        <h2 class="title">违规发言检测</h2>
        <div class="input-area">
            <el-input v-model="inputText" type="textarea" :rows="5" placeholder="请输入需要检测的文本内容" resize="none"></el-input>
            <el-button type="primary" class="detect-button" @click="detectText" :loading="loading">
                检测
            </el-button>
            <el-button type="primary" class="random-button" @click="randomSample" :loading="loading">
                示例
            </el-button>
        </div>
    </div>
</template>

<script>
import { ref } from 'vue'
import { ElMessage } from 'element-plus'

export default {
    emits: ['show-result'],
    setup(props, { emit }) {
        const inputText = ref('')
        const loading = ref(false)

        const detectText = async () => {
            if (!inputText.value.trim()) {
                ElMessage.warning('请输入需要检测的文本内容')
                return
            }

            loading.value = true

            try {
                // 模拟API请求
                const response = await fetch('http://localhost:8000/predict', {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json',
                        'api-key': 'f67dd0f4c8a4be7e1fcfe78b0ff3d0db51865f5511c13ab07e715b230ab3ae4e'
                    },
                    body: JSON.stringify({
                        texts: [inputText.value]
                    })
                })

                const data = await response.json()
                emit('show-result', data)
            } catch (error) {
                ElMessage.error('检测失败，请稍后重试')
                console.error('Detection error:', error)
            } finally {
                loading.value = false
            }
        }

        const randomSample = async () => {
            const texts = [
                '此心也曾渴慕千山 如今爱等风闲 临窗听雨夜 笔忆话梦谈 当年万里觅风月 夜航船 如今江南也不眼馋',
                '韩国CJ在美国偷偷注册饺子专利成功，某宝CJ希杰（必品阁）的旗舰店，某东也有它们品牌的添加剂，各大商超也有，大家不要购买它们的产品',
                '《挑战低价！盛惠双12》 ?罗湖百安居12.12年末钜惠！ ?8.8特权享高达30倍膨胀金 ?全场爆款挑战低价，全城补差！ ?罗湖笋岗宝安北路口??25937576',
                '+3经验想做兼职的加我vxAOC_007',
                '公元1908年11月14日（光绪三十四年十月二十一日），光绪皇帝驾崩，享年38岁',
                '抚苏筝以鸣苇兮，诗楚歌志久远随行',
                '线上兼职，居家可服回复员，男女不限 有意 思我',
                '信任第一? 招兼职? 不信的别来谢谢? 本人自己真实在做海购APP? 每天收入最低60 上不封顶? 想赚钱的我欢迎你来跟我一起做 没素质的和秒删的别来? 相互'
            ]
            let testString = texts[Math.floor(Math.random() * texts.length)]
            inputText.value = testString
            detectText()
        }

        return {
            inputText,
            loading,
            detectText,
            randomSample
        }
    }
}
</script>

<style scoped>
.detection-container {
    max-width: 800px;
    margin: 0 auto;
    padding: 20px;
}

.title {
    text-align: center;
    margin-bottom: 30px;
    color: #333;
}

.input-area {
    display: flex;
    flex-direction: column;
    gap: 20px;
}

.detect-button, .random-button {
    align-self: flex-end;
    width: 120px;
}
</style>