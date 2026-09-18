<route lang="yaml">
meta:
  title: 借阅记录
</route>

<script lang="ts" setup>
import api from '@/api'
import { ElMessage } from 'element-plus'

// 表格数据
const tableData = ref([])
const currentPage = ref(1)
const currentPageSize = ref(10)
const currentCount = ref(0)
const userId = ref('')

function pageRecordSelect(start: number, end: number) {
  try {
    if (userId.value === '') {
      ElMessage.error(`请输入用户ID`)
      return
    }
    api.get('/record/user', {
      params: {
        userId: userId.value,
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
</script>

<template>
  <div>
    <FaPageMain>
      用户借阅记录
    </FaPageMain>
    <FaPageMain>
      <el-input v-model="userId" placeholder="用户ID" clearable style="width: 240px; margin-right: 30px;" />
      <el-button type="primary" native-type="button" plain @click="pageRecordSelect(0, currentPageSize)">
        👀加载
      </el-button>
      <FaDivider />
      <el-table
        :data="tableData" style="width: 100%; font-weight: 200;" stripe mb-4 :border="true"
        :default-sort="{ prop: 'recordId', order: 'ascending' }"
      >
        <el-table-column prop="recordId" label="记录ID" width="200" sortable fixed />
        <el-table-column prop="bookId" label="图书ID" width="150" sortable />
        <el-table-column prop="bookTitle" label="图书名称" width="300" sortable />
        <el-table-column prop="userId" label="用户ID" width="150" sortable />
        <el-table-column prop="uname" label="用户名" width="200" sortable />
        <el-table-column prop="borrowDate" label="借阅时间" width="300" sortable />
        <el-table-column prop="returnDate" label="归还时间" width="300" sortable />
      </el-table>
      <el-pagination
        v-model:current-page="currentPage" v-model:page-size="currentPageSize"
        :page-sizes="[10, 20, 50, 100]" layout="total, sizes, prev, pager, next, jumper" :total="currentCount"
        @size-change="pageRecordSelect(0, currentPageSize)"
        @current-change="pageRecordSelect(currentPageSize * (currentPage - 1) + 1, currentPageSize * currentPage)"
      />
    </FaPageMain>
  </div>
</template>
