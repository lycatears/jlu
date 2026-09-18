import type { RouteRecordRaw } from 'vue-router'

function Layout() {
  return import('@/layouts/index.vue')
}

const routes: RouteRecordRaw = {
  path: '/comment',
  component: Layout,
  redirect: '/comment/page',
  name: 'comment',
  meta: {
    title: '评论管理',
    icon: 'i-heroicons-solid:chat-bubble-left',
  },
  children: [
    {
      path: 'page',
      name: 'allComments',
      component: () => import('@/views/comment/page.vue'),
      meta: {
        title: '所有评论',
      },
    },
    {
      path: 'bookComments',
      name: 'bookComments',
      component: () => import('@/views/comment/bookComments.vue'),
      meta: {
        title: '图书评论信息',
      },
    },
    {
      path: 'userComments',
      name: 'userComments',
      component: () => import('@/views/comment/userComments.vue'),
      meta: {
        title: '用户评论信息',
      },
    },
    {
      path: 'deletedComments',
      name: 'deletedComments',
      component: () => import('@/views/comment/deleted.vue'),
      meta: {
        title: '已删除评论',
      },
    },
  ],
}

export default routes
