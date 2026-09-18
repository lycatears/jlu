<script setup>
import { Plus } from '@element-plus/icons-vue'
import axios from 'axios'
import { ElMessage } from 'element-plus'
import { ref } from 'vue'

const props = defineProps({
  userId: {
    type: String,
    required: true,
  },
})

const imageUrl = ref('')
const selectedFile = ref(null)
const uploading = ref(false)
const uploadProgress = ref(0)
const uploadStatus = ref('')

function beforeAvatarUpload(file) {
  const isJpgOrPng = file.type === 'image/jpeg' || file.type === 'image/png'
  const isLt2M = file.size / 1024 / 1024 < 2

  if (!isJpgOrPng) {
    ElMessage.error('头像图片只能是 JPG/PNG 格式!')
  }
  if (!isLt2M) {
    ElMessage.error('头像图片大小不能超过 2MB!')
  }

  return isJpgOrPng && isLt2M
}

function handleChange(file) {
  // 预览选中的图片
  const reader = new FileReader()
  reader.onload = (e) => {
    imageUrl.value = e.target.result
  }
  reader.readAsDataURL(file.raw)

  selectedFile.value = file.raw
}

async function submitUpload() {
  if (!selectedFile.value) {
    ElMessage.warning('请先选择头像图片')
    return
  }

  uploading.value = true
  uploadProgress.value = 0
  uploadStatus.value = ''

  const file = new FormData()
  file.append('file', selectedFile.value)

  try {
    const response = await axios.post(
      `http://localhost:8080/api/avatar/${localStorage.getItem('uname')}`,
      file,
      {
        headers: {
          'Content-Type': 'multipart/form-data',
          'token': localStorage.getItem('token'),
        },
        onUploadProgress: (progressEvent) => {
          if (progressEvent.total) {
            uploadProgress.value = Math.round(
              (progressEvent.loaded * 100) / progressEvent.total,
            )
          }
        },
      },
    )

    uploadStatus.value = 'success'
    ElMessage.success('头像上传成功')
    // 可以在这里触发父组件更新或其他操作
    emit('upload-success', response.data)
  }
  catch (error) {
    uploadStatus.value = 'exception'
    console.error('上传失败:', error)
  }
  finally {
    uploading.value = false
  }
}
</script>

<template>
  <div class="avatar-upload-container">
    <el-upload
      class="avatar-uploader" action="#" :show-file-list="false" :auto-upload="false" :on-change="handleChange"
      :before-upload="beforeAvatarUpload" enctype="multipart/form-data"
    >
      <img v-if="imageUrl" :src="imageUrl" class="avatar">
      <el-icon v-else class="avatar-uploader-icon">
        <Plus />
      </el-icon>
    </el-upload>

    <el-button type="primary" :loading="uploading" :disabled="!selectedFile" @click="submitUpload">
      上传头像
    </el-button>

    <el-progress
      v-if="uploading" :percentage="uploadProgress" :status="uploadStatus"
      style="width: 300px; margin-top: 20px;"
    />
  </div>
</template>

<style scoped>
/* stylelint-disable order/properties-order */
.avatar-upload-container {
  display: flex;
  flex-direction: column;
  gap: 20px;
  align-items: flex-start;
}

.avatar-uploader {
  border: 1px dashed #d9d9d9;
  cursor: pointer;
  position: relative;
  justify-content: center;
  display: flex;
  align-items: center;
  overflow: hidden;
  width: 178px;
  height: 178px;
  border-radius: 6px;
}

.avatar-uploader:hover {
  border-color: #409eff;
}

.avatar-uploader-icon {
  font-size: 28px;
  color: #8c939d;
}

.avatar {
  width: 100%;
  height: 100%;
  object-fit: cover;
}
</style>
