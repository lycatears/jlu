<route lang="yaml">
meta:
  title: 评论记录
</route>

<script lang="ts" setup>
import api from '@/api'
import { ElMessage, ElMessageBox } from 'element-plus'

// 表格数据
const tableData = ref([])
const currentPage = ref(1)
const currentPageSize = ref(10)
const currentCount = ref(0)

function formatDate(date: Date): string {
  const year = date.getFullYear()
  const month = String(date.getMonth() + 1).padStart(2, '0')
  const day = String(date.getDate()).padStart(2, '0')
  const hours = String(date.getHours()).padStart(2, '0')
  const minutes = String(date.getMinutes()).padStart(2, '0')
  const seconds = String(date.getSeconds()).padStart(2, '0')

  return `${year}-${month}-${day} ${hours}:${minutes}:${seconds}`
}

function pageCommentSelect(start: number, end: number) {
  try {
    api.get('/deletedComment', {
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
        uid: row.userId,
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

function deleteComment(_index: number, row: any) {
  ElMessageBox.confirm(
    `您即将彻底删除评论，此操作将彻底删除该评论，无法恢复。是否确定？`,
    '警告',
    {
      confirmButtonText: '确定',
      cancelButtonText: '取消',
      type: 'warning',
    },
  )
    .then(async () => {
      const res = await api.delete(`/deletedComment/${row.commentId}`)
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

function recoverComment(_index: number, row: any) {
  ElMessageBox.confirm(
    `确定要恢复该评论吗？`,
    '信息',
    {
      confirmButtonText: '确定',
      cancelButtonText: '取消',
      type: 'warning',
    },
  )
    .then(async () => {
      const res = await api.post(`/deletedComment/${row.commentId}`)
      if (typeof res === 'object' && res !== null && 'code' in res && 'message' in res) {
        if (res.code !== 0) {
          ElMessage.error(`恢复失败:${res.message}`)
          return
        }
        ElMessage.success(`恢复成功`)
      }
      else {
        ElMessage.error('恢复失败: 未知错误')
      }
    })
    .catch(() => {
      ElMessage({
        type: 'info',
        message: '操作已取消',
      })
    })
}
</script>

<template>
  <div>
    <FaPageMain>
      已删除评论
    </FaPageMain>
    <FaPageMain>
      <el-button type="primary" native-type="button" plain @click="pageCommentSelect(0, currentPageSize)">
        👀加载
      </el-button>
      <FaDivider />
      <el-table
        :data="tableData" style="width: 100%; font-weight: 200;" stripe mb-4 :border="true"
        :default-sort="{ prop: 'bookId', order: 'ascending' }"
      >
        <el-table-column prop="commentId" label="评论ID" width="100" sortable fixed />
        <el-table-column prop="userId" label="用户ID" width="100" sortable />
        <el-table-column prop="uname" label="用户名" width="150" sortable />
        <el-table-column prop="bookId" label="图书ID" width="100" sortable />
        <el-table-column prop="bookTitle" label="图书名称" width="300" sortable />
        <el-table-column prop="floorId" label="楼层号" width="100" sortable />
        <el-table-column prop="context" label="评论内容" width="300" sortable :show-overflow-tooltip="true" />
        <el-table-column prop="rating" label="用户评分" width="200" sortable>
          <template #default="scope">
            <el-rate v-model="scope.row.rating" disabled show-score text-color="#ff9900" score-template="{value}" />
          </template>
        </el-table-column>
        <el-table-column prop="createTime" label="发表时间" width="120" sortable />
        <el-table-column fixed="right" label="操作" min-width="300">
          <template #default="scope">
            <el-button type="success" plain size="small" @click="recoverComment(scope.$index, scope.row)">
              <el-icon>
                <Select />
              </el-icon>
              恢复
            </el-button>
            <el-button type="warning" plain size="small" @click="banUser(scope.$index, scope.row)">
              <el-icon>
                <CircleClose />
              </el-icon>
              封禁作者
            </el-button>
            <el-button type="danger" plain size="small" @click="deleteComment(scope.$index, scope.row)">
              <el-icon>
                <Delete />
              </el-icon>
              彻底删除
            </el-button>
          </template>
        </el-table-column>
      </el-table>
      <el-pagination
        v-model:current-page="currentPage" v-model:page-size="currentPageSize"
        :page-sizes="[10, 20, 50, 100]" layout="total, sizes, prev, pager, next, jumper" :total="currentCount"
        @size-change="pageCommentSelect(0, currentPageSize)"
        @current-change="pageCommentSelect(currentPageSize * (currentPage - 1) + 1, currentPageSize * currentPage)"
      />
    </FaPageMain>
  </div>
</template>
