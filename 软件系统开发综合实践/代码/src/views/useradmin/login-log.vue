<route lang="yaml">
meta:
  title: 用户管理
</route>

<script lang="ts" setup>
import api from '@/api'
import { ElMessage } from 'element-plus'

// 表格数据
const tableData = ref([])
const currentPage = ref(1)
const currentPageSize = ref(20)
const currentCount = ref(0)
function pageLogSelect(start: number, end: number) {
  try {
    api.get('/loginLog', {
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

function exportTable() {
  const header = ['日志ID', '登录时间', '用户ID', '状态', '登录IP']
  const rows = tableData.value.map(row => [row.id, row.time, row.uid, row.status, row.ip])
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
      用户登录日志
    </FaPageMain>
    <FaPageMain>
      <el-button type="primary" native-type="button" plain @click="pageLogSelect(0, currentPageSize)">
        👀加载近期日志
      </el-button>
      <el-button type="primary" @click="exportTable">
        导出表格
      </el-button>
      <FaDivider />
      <el-table
        :data="tableData" style="width: 100%; font-weight: 200;" stripe mb-4 :border="true"
        :default-sort="{ prop: 'id', order: 'ascending' }"
      >
        <el-table-column prop="id" label="日志ID" width="250" sortable />
        <el-table-column prop="time" label="登录时间" width="420" sortable />
        <el-table-column prop="uid" label="用户ID" width="250" sortable />
        <el-table-column prop="status" label="状态" width="250" sortable />
        <el-table-column prop="ip" label="登录IP" width="250" />
      </el-table>
      <el-pagination
        v-model:current-page="currentPage" v-model:page-size="currentPageSize"
        :page-sizes="[20, 50, 100, 200]" layout="total, sizes, prev, pager, next, jumper" :total="currentCount"
        @size-change="pageLogSelect(0, currentPageSize)"
        @current-change="pageLogSelect(currentPageSize * (currentPage - 1) + 1, currentPageSize * currentPage)"
      />
    </FaPageMain>
  </div>
</template>
