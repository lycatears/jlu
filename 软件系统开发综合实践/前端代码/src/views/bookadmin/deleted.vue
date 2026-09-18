<route lang="yaml">
meta:
  title: 图书管理
</route>

<script lang="ts" setup>
import api from '@/api'
import { ElMessage, ElMessageBox } from 'element-plus'

// 表格数据
const tableData = ref([])
const currentPage = ref(1)
const currentPageSize = ref(10)
const currentCount = ref(0)
function pageBookSelect(start: number, end: number) {
  try {
    api.get('/deletedBook', {
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

function deleteBook(_index: number, row: any) {
  ElMessageBox.confirm(
    `您即将删除图书：${row.bookId}，此操作将永久删除该图书。是否确定？`,
    '警告',
    {
      confirmButtonText: '确定',
      cancelButtonText: '取消',
      type: 'warning',
    },
  )
    .then(async () => {
      const res = await api.delete(`/deletedBook/${row.bookId}`)
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

function recoverBook(_index: number, row: any) {
  ElMessageBox.confirm(
    `您即将恢复图书：${row.bookTitle}，此操作将恢复该图书。是否确定？`,
    '确认操作',
    {
      confirmButtonText: '确定',
      cancelButtonText: '取消',
      type: 'info',
    },
  )
    .then(async () => {
      const res = await api.post(`/deletedBook/${row.bookId}`)
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
      已删除图书信息
    </FaPageMain>
    <FaPageMain>
      <el-button type="primary" native-type="button" plain @click="pageBookSelect(0, currentPageSize)">
        👀加载
      </el-button>
      <FaDivider />
      <el-table
        :data="tableData" style="width: 100%; font-weight: 200;" stripe mb-4 :border="true"
        :default-sort="{ prop: 'bookId', order: 'ascending' }"
      >
        <el-table-column prop="bookId" label="图书ID" width="100" sortable fixed />
        <el-table-column prop="bookTitle" label="图书名称" width="300" sortable />
        <el-table-column prop="bookIsbn" label="ISBN" width="150" sortable />
        <el-table-column prop="bookAuthor" label="作者" width="200" sortable />
        <el-table-column prop="bookYear" label="出版时间" width="120" sortable />
        <el-table-column prop="bookStock" label="库存" width="80" sortable />
        <el-table-column prop="bookStatus" label="状态" width="80" />
        <el-table-column prop="createTime" label="修改时间" width="120" sortable />
        <el-table-column prop="description" label="描述" width="400" :show-overflow-tooltip="true" />
        <el-table-column fixed="right" label="操作" min-width="240">
          <template #default="scope">
            <el-button type="success" plain size="small" @click="recoverBook(scope.$index, scope.row)">
              <el-icon>
                <RefreshRight />
              </el-icon>
              恢复
            </el-button>
            <el-button type="danger" plain size="small" @click="deleteBook(scope.$index, scope.row)">
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
        @size-change="pageBookSelect(0, currentPageSize)"
        @current-change="pageBookSelect(currentPageSize * (currentPage - 1) + 1, currentPageSize * currentPage)"
      />
    </FaPageMain>
  </div>
</template>
