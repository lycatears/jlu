import api from '../index'

export default {
  // 登录
  login: (data: {
    uname: string
    password: string
  }) => api.post('/login', data),

  // 获取权限
  permission: () => api.get('user/permission', {
    baseURL: '/mock/',
  }),

  // 修改密码
  passwordEdit: (data: {
    password: string
    newPassword: string
  }) => api.post('user/password/edit', data, {
    baseURL: '/mock/',
  }),
}
