<route lang="yaml">
meta:
  title: 用户管理
</route>

<script lang="ts" setup>
import api from '@/api'
import { ElMessage, ElMessageBox } from 'element-plus'

// 表格数据
const tableData = ref([])
const currentPage = ref(1)
const currentPageSize = ref(10)
const currentCount = ref(0)
function pageUserSelect(start: number, end: number) {
  try {
    api.get('/deletedUser', {
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

function deleteUser(_index: number, row: any) {
  ElMessageBox.confirm(
    `您即将删除用户：${row.uname}，此操作将永久删除该用户。是否确定？`,
    '警告',
    {
      confirmButtonText: '确定',
      cancelButtonText: '取消',
      type: 'warning',
    },
  )
    .then(async () => {
      const res = await api.delete(`/deletedUser/${row.uid}`)
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

function recoverUser(_index: number, row: any) {
  ElMessageBox.confirm(
    `您即将恢复用户：${row.uname}，此操作将恢复该用户。是否确定？`,
    '确认操作',
    {
      confirmButtonText: '确定',
      cancelButtonText: '取消',
      type: 'info',
    },
  )
    .then(async () => {
      const res = await api.post(`/deletedUser/${row.uid}`)
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
      已删除用户信息
    </FaPageMain>
    <FaPageMain>
      <el-button type="primary" native-type="button" plain @click="pageUserSelect(0, currentPageSize)">
        👀加载
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
            <el-button type="success" plain size="small" @click="recoverUser(scope.$index, scope.row)">
              <el-icon>
                <RefreshRight />
              </el-icon>
              恢复
            </el-button>
            <el-button type="danger" plain size="small" @click="deleteUser(scope.$index, scope.row)">
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
        @size-change="pageUserSelect(0, currentPageSize)"
        @current-change="pageUserSelect(currentPageSize * (currentPage - 1) + 1, currentPageSize * currentPage)"
      />
    </FaPageMain>
  </div>
</template>
