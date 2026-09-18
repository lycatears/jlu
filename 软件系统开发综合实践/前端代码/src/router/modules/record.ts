import type { RouteRecordRaw } from 'vue-router'

function Layout() {
  return import('@/layouts/index.vue')
}

const routes: RouteRecordRaw = {
  path: '/records',
  component: Layout,
  redirect: '/records/page',
  name: 'records',
  meta: {
    title: '借阅记录',
    icon: 'i-heroicons-solid:bars-4',
  },
  children: [
    {
      path: 'page',
      name: 'allBorrowRecords',
      component: () => import('@/views/records/page.vue'),
      meta: {
        title: '所有借阅记录',
      },
    },
    {
      path: 'bookRecords',
      name: 'bookRecords',
      component: () => import('@/views/records/bookRecords.vue'),
      meta: {
        title: '图书借阅记录',
      },
    },
    {
      path: 'userRecords',
      name: 'userRecords',
      component: () => import('@/views/records/userRecords.vue'),
      meta: {
        title: '用户借阅记录',
      },
    },
  ],
}

export default routes
