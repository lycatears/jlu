<script setup lang="ts">
import api from '@/api'
import { FormControl, FormField, FormItem, FormMessage } from '@/ui/shadcn/ui/form'
import { toTypedSchema } from '@vee-validate/zod'
import { ElMessage } from 'element-plus'
import { useForm } from 'vee-validate'
import * as z from 'zod'

defineOptions({
  name: 'RegisterForm',
})

const props = defineProps<{
  uname?: string
}>()

const emits = defineEmits<{
  onLogin: [uname?: string]
  onRegister: [uname?: string]
}>()

const loading = ref(false)

const form = useForm({
  validationSchema: toTypedSchema(
    z.object({
      uname: z.string().min(1, '请输入用户名').max(16, '用户名长度为1到16位'),
      email: z.string().min(1, '请输入邮箱').email('请输入正确的邮箱'),
      password: z.string().min(1, '请输入密码').min(6, '密码长度为6到32位').max(32, '密码长度为6到32位'),
      checkPassword: z.string().min(1, '请再次输入密码'),
    }).refine(data => data.password === data.checkPassword, {
      message: '两次输入的密码不一致',
      path: ['checkPassword'],
    }),
  ),
  initialValues: {
    uname: props.uname ?? '',
    email: '',
    password: '',
    checkPassword: '',
  },
})
const onSubmit = form.handleSubmit(async (values) => {
  loading.value = true
  const res = await api.post('/register', values)
  if ('code' in res && 'message' in res) {
    if (res.code === 0) {
      ElMessage.success('注册成功')
      emits('onRegister', values.uname)
    }
    else {
      ElMessage.error(res.message as string)
    }
  }
})
</script>

<template>
  <div class="min-h-500px w-full flex-col-stretch-center p-12">
    <form @submit="onSubmit">
      <div class="mb-8 space-y-2">
        <h3 class="text-4xl color-[var(--el-text-color-primary)] font-bold">
          探索从这里开始 🚀
        </h3>
      </div>
      <FormField v-slot="{ componentField, errors }" name="email">
        <FormItem class="relative pb-6 space-y-0">
          <FormControl>
            <FaInput
              type="email" placeholder="请输入邮箱" class="w-full" :class="errors.length && 'border-destructive'"
              v-bind="componentField"
            />
          </FormControl>
          <Transition
            enter-active-class="transition-opacity" enter-from-class="opacity-0"
            leave-active-class="transition-opacity" leave-to-class="opacity-0"
          >
            <FormMessage class="absolute bottom-1 text-xs" />
          </Transition>
        </FormItem>
      </FormField>
      <FormField v-slot="{ componentField, errors }" name="uname">
        <FormItem class="relative pb-6 space-y-0">
          <FormControl>
            <FaInput
              type="text" placeholder="请输入用户名" class="w-full" :class="errors.length && 'border-destructive'"
              v-bind="componentField"
            />
          </FormControl>
          <Transition
            enter-active-class="transition-opacity" enter-from-class="opacity-0"
            leave-active-class="transition-opacity" leave-to-class="opacity-0"
          >
            <FormMessage class="absolute bottom-1 text-xs" />
          </Transition>
        </FormItem>
      </FormField>
      <FormField v-slot="{ componentField, value, errors }" name="password">
        <FormItem class="relative pb-6 space-y-0">
          <FormControl>
            <FaInput
              type="password" placeholder="请输入密码" class="w-full" :class="errors.length && 'border-destructive'"
              v-bind="componentField"
            />
          </FormControl>
          <FormDescription>
            <FaPasswordStrength :password="value" class="mt-2" />
          </FormDescription>
          <Transition
            enter-active-class="transition-opacity" enter-from-class="opacity-0"
            leave-active-class="transition-opacity" leave-to-class="opacity-0"
          >
            <FormMessage class="absolute bottom-1 text-xs" />
          </Transition>
        </FormItem>
      </FormField>
      <FormField v-slot="{ componentField, errors }" name="checkPassword">
        <FormItem class="relative pb-6 space-y-0">
          <FormControl>
            <FaInput
              type="password" placeholder="请再次输入密码" class="w-full" :class="errors.length && 'border-destructive'"
              v-bind="componentField"
            />
          </FormControl>
          <Transition
            enter-active-class="transition-opacity" enter-from-class="opacity-0"
            leave-active-class="transition-opacity" leave-to-class="opacity-0"
          >
            <FormMessage class="absolute bottom-1 text-xs" />
          </Transition>
        </FormItem>
      </FormField>
      <FaButton :loading="loading" size="lg" class="mt-4 w-full" type="submit">
        注册
      </FaButton>
      <div class="mt-4 flex-center gap-2 text-sm">
        <span class="text-secondary-foreground op-50">已经有帐号?</span>
        <FaButton variant="link" class="h-auto p-0" @click="emits('onLogin', form.values.uname)">
          去登录
        </FaButton>
      </div>
    </form>
  </div>
</template>
