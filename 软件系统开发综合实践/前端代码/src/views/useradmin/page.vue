<route lang="yaml">
meta:
  title: 用户管理
</route>

<script lang="ts" setup>
import api from '@/api'
import { ElMessage, ElMessageBox } from 'element-plus'

interface User {
  uname: string
  email: string
  password: string
  avatar: string
  group: string
  slogan: string
}

// 表格数据
const tableData = ref([])
const newUserDialogFormVisible = ref(false)
const editUserDialogFormVisible = ref(false)
const formLabelWidth = '140px'
const currentPage = ref(1)
const currentPageSize = ref(10)
const currentCount = ref(0)
const keyword = ref('')

const rules = {
  uname: [
    { required: true, message: '请输入用户名', trigger: 'blur' },
    { type: 'string', min: 1, max: 16, message: '长度在 1 到 16 个字符', trigger: 'blur' },
  ],
  email: [
    { required: true, message: '请输入邮箱地址', trigger: 'blur' },
    { type: 'email', message: '请输入正确的邮箱地址', trigger: 'blur' },
  ],
  password: [
    { required: true, message: '请输入密码', trigger: 'blur' },
    { type: 'string', min: 6, max: 32, message: '长度在 6 到 32 个字符', trigger: 'blur' },
  ],
}

const editRules = {
  uname: [
    { required: false, message: '请输入用户名', trigger: 'blur' },
    { type: 'string', min: 1, max: 16, message: '长度在 1 到 16 个字符', trigger: 'blur' },
  ],
  email: [
    { required: false, message: '请输入邮箱地址', trigger: 'blur' },
    { type: 'email', message: '请输入正确的邮箱地址', trigger: 'blur' },
  ],
  password: [
    { required: false, message: '请输入密码', trigger: 'blur' },
    { type: 'string', min: 6, max: 32, message: '长度在 6 到 32 个字符', trigger: 'blur' },
  ],
  avatar: [
    { required: false, message: '请输入头像地址', trigger: 'blur' },
  ],
  group: [
    { required: false, message: '请输入用户组', trigger: 'blur' },
  ],
  slogan: [
    { required: false, message: '请输入个性签名', trigger: 'blur' },
    { type: 'string', min: 0, max: 32, message: '长度在 0 到 32 个字符', trigger: 'blur' },
  ],
}

const options = [
  {
    value: 'admin',
    label: '管理员',
  },
  {
    value: 'user',
    label: '普通用户',
  },
]

const formRef = ref()
const editRef = ref()

// function _htmlEscape(str: string): string {
//   // 定义需要转义的字符映射表
//   const htmlEscapes: Record<string, string> = {
//     '&': '&amp;',
//     '<': '&lt;',
//     '>': '&gt;',
//     '"': '&quot;',
//     '\'': '&#x27;',
//     '`': '&#x60;',
//   }

//   // 编译正则表达式以提升性能
//   const escapeRegex = /[&<>"'`]/g

//   // 输入校验：确保输入是字符串类型
//   if (typeof str !== 'string') {
//     throw new TypeError('Expected a string as input')
//   }

//   // 如果字符串中没有需要转义的字符，直接返回原字符串
//   if (!escapeRegex.test(str)) {
//     return str
//   }

//   // 替换需要转义的字符
//   return str.replace(escapeRegex, char => htmlEscapes[char as string] || char)
// }

function formatDate(date: Date): string {
  const year = date.getFullYear()
  const month = String(date.getMonth() + 1).padStart(2, '0')
  const day = String(date.getDate()).padStart(2, '0')
  const hours = String(date.getHours()).padStart(2, '0')
  const minutes = String(date.getMinutes()).padStart(2, '0')
  const seconds = String(date.getSeconds()).padStart(2, '0')

  return `${year}-${month}-${day} ${hours}:${minutes}:${seconds}`
}

function pageUserSelect(start: number, end: number) {
  try {
    api.get('/user', {
      params: {
        start,
        end,
      },
    }).then((response) => {
      ElMessage.success(`查询成功`)
      tableData.value = response.data.rows
      currentPage.value = Math.floor(start / currentPageSize.value) + 1
      currentCount.value = response.data.count
    })
  }
  catch (error) {
    ElMessage.error(`${error}`)
  }
}

function search() {
  try {
    api.get(`/user/search`, {
      params: {
        keyword: keyword.value,
      },
    }).then((response) => {
      ElMessage.success(`查询成功`)
      tableData.value = response.data.rows
    })
  }
  catch (error) {
    ElMessage.error(`${error}`)
  }
}

const form = reactive({
  uname: '',
  email: '',
  password: '',
})

const editUserFrom = reactive({
  uid: '',
  uname: '',
  email: '',
  hashPassword: '',
  avatar: '',
  group: '',
  slogan: '',
})

function deleteUser(_index: number, row: any) {
  ElMessageBox.confirm(
    `您即将删除用户：${row.uname}，此操作将删除该用户，稍后您可在“已删除用户”中恢复。是否确定？`,
    '警告',
    {
      confirmButtonText: '确定',
      cancelButtonText: '取消',
      type: 'warning',
    },
  )
    .then(async () => {
      const res = await api.delete(`/user/${row.uid}`)
      if (typeof res === 'object' && res !== null && 'code' in res && 'message' in res) {
        if (res.code !== 0) {
          ElMessage.error(`删除失败:${res.message}`)
          return
        }
        ElMessage.success(`删除成功`)
      }
      else {
        ElMessage.error('删除失败: 未知错误')
      }
    })
    .catch(() => {
      ElMessage({
        type: 'info',
        message: '操作已取消',
      })
    })
}

function banUser(_index: number, row: any) {
  ElMessageBox.prompt('输入封禁时长（单位：天）', '封禁', {
    confirmButtonText: '封禁',
    cancelButtonText: '取消',
    inputPattern:
      /^[1-9]\d*$/,
    inputErrorMessage: '输入的时长无效',
  })
    .then(async ({ value }) => {
      const date = new Date()
      date.setDate(date.getDate() + Number.parseInt(value))

      const res = await api.put(`/user`, {
        uid: row.uid,
        enableAfter: formatDate(date),
      }, {
        headers: {
          'Content-Type': 'application/json',
        },
      })
      if (typeof res === 'object' && res !== null && 'code' in res && 'message' in res) {
        if (res.code !== 0) {
          ElMessage.error(`封禁失败:${res.message}`)
          return
        }
        ElMessage.success(`封禁成功`)
      }
    })
    .catch(() => {
      ElMessage({
        type: 'info',
        message: '操作已取消',
      })
    })
}

function editUser() {
  editRef.value.validate(async (valid: any) => {
    if (valid) {
      try {
        const response = await api.put('/user', editUserFrom)
        const { code, data } = response as any // 假设后端返回的数据结构为 { code, message, data }
        if (code === 0 && !data) {
          ElMessage.success('修改成功')
        }
        else {
          ElMessage.error(`修改失败:${data}`) // 显示后端返回的错误信息
        }
      }
      catch (error) {
        console.error(error)
        ElMessage.error('请求失败，请稍后再试')
      }
      finally {
        editUserDialogFormVisible.value = false
      }
    }
    else {
      return false
    }
  })
}

async function initEditUserDialog(_index: number, row: any) {
  try {
    let key: keyof User
    const res = await api.get(`/user/${row.uid}`)
    const user = res.data as User
    for (key in user) {
      editUserFrom[key] = user[key]
    }

    editUserFrom.uid = row.uid
    editUserDialogFormVisible.value = true
  }
  catch (error) {
    ElMessage.error(`${error}`)
    console.error(error)
  }
}

async function newUser() {
  formRef.value.validate(async (valid: any) => {
    if (valid) {
      try {
        // form.uname = htmlEscape(form.uname);
        const response = await api.post('/user', form) as { code?: number, message?: string, data?: string }
        const { code, message, data } = response // 假设后端返回的数据结构为 { code, message, data }
        if (code === 0 && !data) {
          ElMessage.success('添加成功')
        }
        else {
          ElMessage.error(`添加失败:${message || data}`) // 显示后端返回的错误信息
        }
      }
      catch (error) {
        console.error(error)
        ElMessage.error('用户已存在，请更换用户名重试')
      }
      finally {
        newUserDialogFormVisible.value = false
      }
    }
    else {
      return false
    }
  })
}

function exportTable() {
  const header = ['UID', '用户名', '邮箱', '用户组', '签名', '注册时间', '最后登录时间', '启用时间']
  const rows = tableData.value.map(row => [row.uid, row.uname, row.email, row.group, row.slogan, row.registerTime, row.lastLoginTime, row.enableAfter])
  const csvContent
    = `\uFEFF${// 防止中文乱码
      [header, ...rows].map(e => e.join(',')).join('\n')}`

  const blob = new Blob([csvContent], { type: 'text/csv;charset=utf-8;' })
  const url = URL.createObjectURL(blob)
  const link = document.createElement('a')
  link.href = url
  link.setAttribute('download', '表格数据.csv')
  document.body.appendChild(link)
  link.click()
  document.body.removeChild(link)
}
</script>

<template>
  <div>
    <FaPageMain>
      注册用户信息
    </FaPageMain>
    <FaPageMain>
      <el-button type="primary" native-type="button" plain @click="pageUserSelect(0, currentPageSize)">
        👀加载
      </el-button>
      <el-button type="primary" @click="exportTable">
        导出表格
      </el-button>
      <el-button type="success" plain @click="newUserDialogFormVisible = true">
        <el-icon>
          <Plus />
        </el-icon>
        新增
      </el-button>
      <el-input v-model="keyword" placeholder="关键字查询" clearable style="width: 240px; margin-left: 30px;" />
      <el-button type="primary" native-type="button" plain @click="search">
        搜索
      </el-button>
      <FaDivider />
      <el-table
        :data="tableData" style="width: 100%; font-weight: 200;" stripe mb-4 :border="true"
        :default-sort="{ prop: 'uid', order: 'ascending' }"
      >
        <el-table-column prop="uid" label="UID" width="80" sortable fixed />
        <el-table-column prop="uname" label="用户名" width="150" sortable />
        <el-table-column prop="email" label="邮箱" width="150" sortable />
        <el-table-column prop="registerTime" label="注册时间" width="120" sortable />
        <el-table-column prop="lastLoginTime" label="上次登录" width="120" sortable />
        <el-table-column prop="enableAfter" label="启用时间" width="120" sortable />
        <!-- <el-table-column prop="avatar" label="头像" width="120" /> -->
        <el-table-column prop="group" label="用户组" width="120" sortable />
        <el-table-column prop="slogan" label="个性签名" width="120" />
        <el-table-column fixed="right" label="操作" min-width="240">
          <template #default="scope">
            <el-button type="success" plain size="small" @click="initEditUserDialog(scope.$index, scope.row)">
              <el-icon>
                <Edit />
              </el-icon>
              编辑
            </el-button>
            <el-button type="danger" plain size="small" @click="deleteUser(scope.$index, scope.row)">
              <el-icon>
                <Delete />
              </el-icon>
              删除
            </el-button>
            <el-button type="warning" plain size="small" @click="banUser(scope.$index, scope.row)">
              <el-icon>
                <CircleClose />
              </el-icon>
              封禁
            </el-button>
          </template>
        </el-table-column>
      </el-table>
      <el-pagination
        v-model:current-page="currentPage" v-model:page-size="currentPageSize"
        :page-sizes="[10, 20, 50, 100]" layout="total, sizes, prev, pager, next, jumper" :total="currentCount"
        @size-change="pageUserSelect(0, currentPageSize)"
        @current-change="pageUserSelect(currentPageSize * (currentPage - 1) + 1, currentPageSize * currentPage)"
      />
    </FaPageMain>
    <el-dialog v-model="newUserDialogFormVisible" title="添加新用户" width="500">
      <el-form ref="formRef" :model="form" :rules="rules">
        <el-form-item label="用户名" :label-width="formLabelWidth" prop="uname">
          <el-input
            v-model="form.uname" autocomplete="off" clearable minlength="1" maxlength="16" show-word-limit
            placeholder="请输入用户名" @keyup="form.uname = form.uname.replace(/\*\'/g, '')"
          />
        </el-form-item>
        <el-form-item label=" 邮箱" :label-width="formLabelWidth" prop="email">
          <el-input v-model="form.email" autocomplete="off" clearable placeholder="请输入邮箱地址" />
        </el-form-item>
        <el-form-item label="密码" :label-width="formLabelWidth" prop="password">
          <el-input
            v-model="form.password" type="password" autocomplete="off" show-password maxlength="32"
            minlength="6" placeholder="6-32位字母、数字、特殊符号"
          />
        </el-form-item>
      </el-form>
      <template #footer>
        <div class="dialog-footer">
          <el-button @click="newUserDialogFormVisible = false">
            取消
          </el-button>
          <el-button type="primary" @click="newUser">
            添加
          </el-button>
        </div>
      </template>
    </el-dialog>

    <!-- 编辑用户对话框 -->
    <el-dialog v-model="editUserDialogFormVisible" title="编辑用户信息" width="500">
      <el-form ref="editRef" :model="editUserFrom" :rules="editRules">
        <el-form-item label="用户名" :label-width="formLabelWidth" prop="uname">
          <el-input
            v-model="editUserFrom.uname" autocomplete="off" clearable minlength="1" maxlength="16"
            show-word-limit placeholder="请输入用户名"
            @keyup="editUserFrom.uname = editUserFrom.uname.replace(/\*\'/g, '')"
          />
        </el-form-item>
        <el-form-item label="邮箱" :label-width="formLabelWidth" prop="email">
          <el-input v-model="editUserFrom.email" autocomplete="off" clearable placeholder="请输入邮箱地址" />
        </el-form-item>
        <el-form-item label="密码" :label-width="formLabelWidth" prop="password">
          <el-input
            v-model="editUserFrom.hashPassword" type="password" autocomplete="off" show-password maxlength="32"
            minlength="6" placeholder="6-32位字母、数字、特殊符号"
          />
        </el-form-item>
        <el-form-item label="头像" :label-width="formLabelWidth" prop="avatar">
          <el-input v-model="editUserFrom.avatar" autocomplete="off" clearable placeholder="头像（暂缺）" />
        </el-form-item>
        <el-form-item label="用户组" :label-width="formLabelWidth" prop="group">
          <!-- <el-input v-model="editUserFrom.group" autocomplete="off" clearable placeholder="请选择用户组" /> -->
          <el-select v-model="editUserFrom.group" placeholder="请选择">
            <el-option v-for="item in options" :key="item.value" :label="item.label" :value="item.value" />
          </el-select>
        </el-form-item>
        <el-form-item label="个性签名" :label-width="formLabelWidth" prop="slogan">
          <el-input v-model="editUserFrom.slogan" autocomplete="off" clearable placeholder="请输入个性签名" />
        </el-form-item>
      </el-form>
      <template #footer>
        <div class="dialog-footer">
          <el-button @click="editUserDialogFormVisible = false">
            取消
          </el-button>
          <el-button type="primary" @click="editUser">
            确定
          </el-button>
        </div>
      </template>
    </el-dialog>
  </div>
</template>
