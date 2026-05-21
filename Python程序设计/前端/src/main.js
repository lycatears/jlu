import './assets/main.css'
import { createApp } from 'vue'
import ElementPlus from 'element-plus'
import 'element-plus/dist/index.css'
import 'element-plus/theme-chalk/dark/css-vars.css'
import * as echarts from 'echarts'
import App from './App.vue'

const app = createApp(App)

app.use(ElementPlus)
app.config.globalProperties.$echarts = echarts
app.mount('#app')
