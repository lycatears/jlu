<route lang="yaml">
meta:
  title: 图书管理
</route>

<script lang="ts" setup>
import api from '@/api'
import { ElMessage, ElMessageBox } from 'element-plus'

// 表格数据
const tableData = ref([])
const newBookDialogFormVisible = ref(false)
const editBookDialogFormVisible = ref(false)
const formLabelWidth = '140px'
const currentPage = ref(1)
const currentPageSize = ref(10)
const currentCount = ref(0)

const rules = {
  bookTitle: [
    { required: true, message: '请输入图书名称', trigger: 'blur' },
    { type: 'string', min: 1, max: 255, message: '长度在 1 到 255 个字符', trigger: 'blur' },
  ],
  bookIsbn: [
    { required: false, message: '请输入图书ISBN', trigger: 'blur' },
    { type: 'string', message: '请输入图书ISBN', trigger: 'blur' },
  ],
  bookAuthor: [
    { required: true, message: '请输入作者信息', trigger: 'blur' },
    { type: 'string', min: 1, max: 255, message: '长度在 1 到 255 个字符', trigger: 'blur' },
  ],
  bookYear: [
    { required: false, message: '请输入出版时间', trigger: 'blur' },
  ],
  bookStock: [
    { required: true, message: '请输入库存数量', trigger: 'blur' },
    { type: 'string', message: '请输入数字', trigger: 'blur' },
  ],
  description: [
    { required: false, message: '请输入图书描述', trigger: 'blur' },
    { type: 'string', min: 0, max: 1000, message: '长度在 0 到 1000 个字符', trigger: 'blur' },
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

const formRef = ref()
const editRef = ref()

function formatDate(date: Date): string {
  const year = date.getFullYear()
  const month = String(date.getMonth() + 1).padStart(2, '0')
  const day = String(date.getDate()).padStart(2, '0')
  const hours = String(date.getHours()).padStart(2, '0')
  const minutes = String(date.getMinutes()).padStart(2, '0')
  const seconds = String(date.getSeconds()).padStart(2, '0')

  return `${year}-${month}-${day} ${hours}:${minutes}:${seconds}`
}

function pageBookSelect(start: number, end: number) {
  try {
    api.get('/book', {
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

const form = reactive({
  bookTitle: '',
  bookAuthor: '',
  bookIsbn: '',
  bookYear: '',
  bookStock: '',
  description: '',
  status: 'OK',
  createTime: '',
  tags: [] as string[],
})

const editBookFrom = reactive({
  uid: '',
  uname: '',
  email: '',
  hashPassword: '',
  avatar: '',
  group: '',
  slogan: '',
})

function deleteBook(_index: number, row: any) {
  ElMessageBox.confirm(
    `您即将删除图书：${row.bookTitle}，此操作将删除该图书，稍后您可在“已删除图书”中恢复。是否确定？`,
    '警告',
    {
      confirmButtonText: '确定',
      cancelButtonText: '取消',
      type: 'warning',
    },
  )
    .then(async () => {
      const res = await api.delete(`/book/${row.bookId}`)
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

function editBook() {
  editRef.value.validate(async (valid: any) => {
    if (valid) {
      try {
        const response = await api.put('/book', editBookFrom)
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
        editBookDialogFormVisible.value = false
      }
    }
    else {
      return false
    }
  })
}

async function initEditBookDialog(_index: number, row: any) {
  try {
    let key: keyof Book
    const res = await api.get(`/book/${row.uid}`)
    const Book = res.data as Book
    for (key in Book) {
      editBookFrom[key] = Book[key]
    }

    editBookFrom.uid = row.uid
    editBookDialogFormVisible.value = true
  }
  catch (error) {
    ElMessage.error(`${error}`)
    console.error(error)
  }
}

async function newBook() {
  formRef.value.validate(async (valid: any) => {
    if (valid) {
      try {
        // form.uname = htmlEscape(form.uname);
        form.createTime = formatDate(new Date())
        const response = await api.post('/book', form) as { code?: number, message?: string, data?: string }
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
        ElMessage.error('请求失败，请稍后再试')
      }
      finally {
        newBookDialogFormVisible.value = false
      }
    }
    else {
      return false
    }
  })
}

function exportTable() {
  const header = ['图书ID', '图书名称', 'ISBN', '出版年份', '库存量', '描述', '状态', '创建时间']
  const rows = tableData.value.map(row => [row.bookId, row.bookTitle, row.bookIsbn, row.bookYear, row.bookStock, row.description, row.status, row.createTime])
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
      所有图书信息
    </FaPageMain>
    <FaPageMain>
      <el-button type="primary" native-type="button" plain @click="pageBookSelect(0, currentPageSize)">
        👀加载
      </el-button>
      <el-button type="success" plain @click="newBookDialogFormVisible = true">
        <el-icon>
          <Plus />
        </el-icon>
        新增
      </el-button>
      <el-button type="primary" @click="exportTable">
        导出表格
      </el-button>
      <FaDivider />
      <el-table :data="tableData" style="width: 100%; font-weight: 200;" stripe mb-4 :border="true"
        :default-sort="{ prop: 'bookId', order: 'ascending' }">
        <el-table-column prop="bookId" label="图书ID" width="100" sortable fixed />
        <el-table-column prop="bookTitle" label="图书名称" width="300" sortable />
        <el-table-column prop="bookIsbn" label="ISBN" width="150" sortable />
        <el-table-column prop="bookAuthor" label="作者" width="200" sortable />
        <el-table-column prop="bookYear" label="出版时间" width="120" sortable />
        <el-table-column prop="bookStock" label="库存" width="80" sortable />
        <el-table-column prop="bookStatus" label="状态" width="80" />
        <el-table-column prop="createTime" label="修改时间" width="120" sortable />
        <el-table-column prop="description" label="描述" width="400" :show-overflow-tooltip="true" />
        <el-table-column fixed="right" label="操作" min-width="180">
          <template #default="scope">
            <el-button type="success" plain size="small" @click="initEditBookDialog(scope.$index, scope.row)">
              <el-icon>
                <Edit />
              </el-icon>
              编辑
            </el-button>
            <el-button type="danger" plain size="small" @click="deleteBook(scope.$index, scope.row)">
              <el-icon>
                <Delete />
              </el-icon>
              删除
            </el-button>
          </template>
        </el-table-column>
      </el-table>
      <el-pagination v-model:current-page="currentPage" v-model:page-size="currentPageSize"
        :page-sizes="[10, 20, 50, 100]" layout="total, sizes, prev, pager, next, jumper" :total="currentCount"
        @size-change="pageBookSelect(0, currentPageSize)"
        @current-change="pageBookSelect(currentPageSize * (currentPage - 1) + 1, currentPageSize * currentPage)" />
    </FaPageMain>

    <!-- 新增图书对话框 -->
    <el-dialog v-model="newBookDialogFormVisible" title="添加新图书" width="500">
      <el-form ref="formRef" :model="form" :rules="rules">
        <el-form-item label="图书名称" :label-width="formLabelWidth" prop="bookTitle">
          <el-input v-model="form.bookTitle" autocomplete="off" clearable minlength="1" maxlength="255" show-word-limit
            placeholder="请输入图书名称" @keyup="form.bookTitle = form.bookTitle.replace(/\*\'/g, '')" />
        </el-form-item>
        <el-form-item label="ISBN" :label-width="formLabelWidth" prop="bookIsbn">
          <el-input v-model="form.bookIsbn" autocomplete="off" clearable placeholder="请输入图书ISBN" />
        </el-form-item>
        <el-form-item label="作者" :label-width="formLabelWidth" prop="bookAuthor">
          <el-input v-model="form.bookAuthor" type="text" autocomplete="off" maxlength="255" show-word-limit
            minlength="6" placeholder="请输入图书作者" />
        </el-form-item>
        <el-form-item label="出版时间" :label-width="formLabelWidth" prop="bookYear">
          <el-input v-model="form.bookYear" type="text" autocomplete="off" maxlength="255" minlength="0"
            placeholder="请输入图书出版时间" />
        </el-form-item>
        <el-form-item label="图书库存" :label-width="formLabelWidth" prop="bookStock">
          <el-input v-model="form.bookStock" type="number" autocomplete="off" placeholder="请输入图书当前库存" />
        </el-form-item>
        <el-form-item label="简介" :label-width="formLabelWidth" prop="bookYear">
          <el-input v-model="form.description" type="textarea" autocomplete="off" maxlength="1000" minlength="0"
            show-word-limit placeholder="请输入图书简介，可以包含图书内容、框架、适用人群等" />
        </el-form-item>
        <el-form-item label="图书标签" :label-width="formLabelWidth" prop="tags">
          <el-input-tag v-model="form.tags" :max="3" placeholder="回车添加标签，不超过3个" />
        </el-form-item>
      </el-form>
      <template #footer>
        <div class="dialog-footer">
          <el-button @click="newBookDialogFormVisible = false">
            取消
          </el-button>
          <el-button type="primary" @click="newBook">
            添加
          </el-button>
        </div>
      </template>
    </el-dialog>

    <!-- 编辑用户对话框 -->
    <el-dialog v-model="editBookDialogFormVisible" title="编辑用户信息" width="500">
      <el-form ref="editRef" :model="editBookFrom" :rules="editRules">
        <el-form-item label="用户名" :label-width="formLabelWidth" prop="uname">
          <el-input v-model="editBookFrom.uname" autocomplete="off" clearable minlength="1" maxlength="16"
            show-word-limit placeholder="请输入用户名"
            @keyup="editBookFrom.uname = editBookFrom.uname.replace(/\*\'/g, '')" />
        </el-form-item>
        <el-form-item label="邮箱" :label-width="formLabelWidth" prop="email">
          <el-input v-model="editBookFrom.email" autocomplete="off" clearable placeholder="请输入邮箱地址" />
        </el-form-item>
        <el-form-item label="密码" :label-width="formLabelWidth" prop="password">
          <el-input v-model="editBookFrom.hashPassword" type="password" autocomplete="off" show-password maxlength="32"
            minlength="6" placeholder="6-32位字母、数字、特殊符号" />
        </el-form-item>
        <el-form-item label="头像" :label-width="formLabelWidth" prop="avatar">
          <el-input v-model="editBookFrom.avatar" autocomplete="off" clearable placeholder="头像（暂缺）" />
        </el-form-item>
        <el-form-item label="用户组" :label-width="formLabelWidth" prop="group">
          <!-- <el-input v-model="editBookFrom.group" autocomplete="off" clearable placeholder="请选择用户组" /> -->
          <el-select v-model="editBookFrom.group" placeholder="请选择">
            <el-option v-for="item in options" :key="item.value" :label="item.label" :value="item.value" />
          </el-select>
        </el-form-item>
        <el-form-item label="个性签名" :label-width="formLabelWidth" prop="slogan">
          <el-input v-model="editBookFrom.slogan" autocomplete="off" clearable placeholder="请输入个性签名" />
        </el-form-item>
        <el-form-item label="图书标签" :label-width="formLabelWidth" prop="tags">
          <el-input-tag v-model="editBookFrom.tags" :max="3" placeholder="enter up to 3 tags" />
        </el-form-item>
      </el-form>
      <template #footer>
        <div class="dialog-footer">
          <el-button @click="editBookDialogFormVisible = false">
            取消
          </el-button>
          <el-button type="primary" @click="editBook">
            确定
          </el-button>
        </div>
      </template>
    </el-dialog>
  </div>
</template>
