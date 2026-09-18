import type { RouteRecordRaw } from 'vue-router'

function Layout() {
  return import('@/layouts/index.vue')
}

const routes: RouteRecordRaw = {
  path: '/bookadmin',
  component: Layout,
  redirect: '/bookadmin/page',
  name: 'bookadmin',
  meta: {
    title: '图书管理',
    icon: 'i-heroicons-solid:book-open',
  },
  children: [
    {
      path: 'page',
      name: 'bookAdminPage',
      component: () => import('@/views/bookadmin/page.vue'),
      meta: {
        title: '所有图书信息',
      },
    },
    {
      path: 'deletedBooks',
      name: 'deletedBooks',
      component: () => import('@/views/bookadmin/deleted.vue'),
      meta: {
        title: '已删除图书',
      },
    },
  ],
}

export default routes
