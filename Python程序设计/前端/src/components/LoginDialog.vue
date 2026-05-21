<template>
    <el-dialog :model-value="visible" title="用户登录" width="30%" @close="$emit('close')">
        <el-form :model="form" label-width="80px">
            <el-form-item label="用户名">
                <el-input v-model="form.username" placeholder="请输入用户名"></el-input>
            </el-form-item>
            <el-form-item label="密码">
                <el-input v-model="form.password" type="password" placeholder="请输入密码"></el-input>
            </el-form-item>
        </el-form>
        <template #footer>
            <el-button @click="$emit('close')">取消</el-button>
            <el-button type="primary" @click="handleLogin" :loading="loading">登录</el-button>
        </template>
    </el-dialog>
</template>

<script>
import { ref } from 'vue'
import { ElMessage } from 'element-plus'
import axios from 'axios'

export default {
    props: {
        visible: Boolean
    },
    emits: ['close', 'success'],
    setup(props, { emit }) {
        const form = ref({
            username: '',
            password: ''
        })
        const loading = ref(false)

        const handleLogin = async () => {
            if (!form.value.username || !form.value.password) {
                ElMessage.warning('请输入用户名和密码')
                return
            }

            loading.value = true

            try {
                const response = await axios.post('http://localhost:8000/login', {
                    username: form.value.username,
                    password: form.value.password
                })

                if (response.status === 200) {
                    emit('success', response.data.api_key)
                    ElMessage.success('登录成功')
                }
            } catch (error) {
                if (error.response) {
                    const errorMsg = error.response.data.detail || '登录失败'
                    ElMessage.error(errorMsg)
                } else {
                    ElMessage.error('网络错误，请稍后重试')
                }
            } finally {
                loading.value = false
            }
        }

        return {
            form,
            loading,
            handleLogin
        }
    }
}
</script>