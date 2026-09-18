import type { RouteRecordRaw } from 'vue-router'

function Layout() {
  return import('@/layouts/index.vue')
}

const routes: RouteRecordRaw = {
  path: '/useradmin',
  component: Layout,
  redirect: '/useradmin/page',
  name: 'multilevelMenuExample',
  meta: {
    title: '用户管理',
    icon: 'i-heroicons-solid:users',
  },
  children: [
    {
      path: 'all',
      name: 'allUsers',
      component: () => import('@/views/useradmin/page.vue'),
      meta: {
        title: '注册用户信息',
      },
    },
    {
      path: 'deleted',
      name: 'deletedUsers',
      component: () => import('@/views/useradmin/deleted.vue'),
      meta: {
        title: '已删除用户信息',
      },
    },
    {
      path: 'login-log',
      name: 'login-log',
      component: () => import('@/views/useradmin/login-log.vue'),
      meta: {
        title: '用户登录日志',
      },
    },
  ],
}

export default routes
