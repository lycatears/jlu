<route lang="yaml">
meta:
  title: 主页
  icon: ant-design:home-twotone
</route>

<script setup lang="ts">
import api from '@/api'
import * as echarts from 'echarts'
import 'echarts-wordcloud'

const versionType = ref('basic')
watch(versionType, (val) => {
  if (val === 'pro') {
    location.href = `${location.origin}${location.pathname}`.replace('basic-example', 'pro-example')
  }
})

function open(url: string) {
  window.open(url, '_blank')
}

function loadBookYearData() {
  api.get('/chart/book-year').then((res) => {
    const bookYearChart = echarts.init(document.getElementById('book-year-chart'))
    const data = Array.from(res.data) as { year: number, bookCount: number }[]
    const years = data.map(d => d.year)
    const counts = data.map(d => d.bookCount)
    const option = {
      xAxis: { type: 'category', data: years },
      yAxis: { type: 'value' },
      series: [{ type: 'bar', data: counts }],
    }
    bookYearChart.setOption(option)
  })
}

function loadBookTagsData() {
  api.get('/chart/tag-count').then((res) => {
    const bookYearChart = echarts.init(document.getElementById('book-tags-chart'))
    const data: { tagName: string, tagCount: number }[] = Array.from(res.data) as any
    const tags = data.map(d => d.tagName)
    const count = data.map(d => d.tagCount)
    const option = {
      xAxis: { type: 'category', data: tags },
      yAxis: { type: 'value' },
      series: [{ type: 'bar', data: count }],
      itemStyle: {
        shadowBlur: 10,
        shadowColor: 'rgba(166,0,5,0.5)',
        shadowOffsetY: 5,
        color: new echarts.graphic.RadialGradient(0.5, 1, 1, [
          {
            offset: 0,
            color: 'rgb(251,118,134)',
          },
          {
            offset: 1,
            color: 'rgb(230,35,58)',
          },
        ]),
      },
      color: 'rgba(166,0,5,0.5)',
      emphasis: {
        focus: 'self',
      },
      tooltip: {
        trigger: 'item',
        formatter: (params: { data: number, name: string }) => {
          return `${params.name}:${params.data}`
        },
      },
    }
    bookYearChart.setOption(option)
  })
}

async function loadWordCloudDescription() {
  const chart = echarts.init(document.getElementById('word-cloud-description'))
  const { data } = await api.get('http://localhost:8080/api/chart/word-cloud-description')

  chart.setOption({
    series: [{
      type: 'wordCloud',
      shape: 'circle',
      sizeRange: [12, 50],
      rotationRange: [-90, 90],
      textStyle: {
        normal: {
          color: () => `rgb(${[0, 0, 0].map(() => Math.floor(Math.random() * 160)).join(',')})`,
        },
      },
      data,
    }],
  })
}
</script>

<template>
  <div>
    <div class="w-full flex flex-col gap-4 px-4 xl-flex-row">
      <FaPageMain class="m-0 flex-1" title-class="flex flex-wrap items-center justify-between gap-4">
        <template #title>
          <div class="title-info">
            <div>
              <h1 class="c-[#41b883]">
                图书信息词云
              </h1>
            </div>
          </div>
          <div class="ms-auto">
            <FaButton @click="loadWordCloudDescription">
              加载数据
            </FaButton>
          </div>
        </template>
        <div id="word-cloud-description" class="chart" />
      </FaPageMain>

      <!-- <FaPageMain class="m-0 flex-1" title-class="flex flex-wrap items-center justify-between gap-4">
        <template #title>
          <div class="title-info">
            <img src="https://one-step-admin.hurui.me/logo.png">
            <div>
              <h1 class="c-[#67c23a]">
                One-step-admin
              </h1>
              <h2>一款干啥都快人一步的 Vue 中后台系统框架</h2>
            </div>
          </div>
          <div class="ms-auto">
            <FaButton @click="open('https://one-step-admin.hurui.me')">
              访问官网
            </FaButton>
          </div>
        </template>
        <ElCarousel trigger="click" indicator-position="none" :interval="5000" height="250px">
          <ElCarouselItem v-for="(item, index) in oneStepAdminInfo.data" :key="item">
            <ElImage
              :src="item" fit="cover" style="width: 100%; height: 250px; margin: auto; cursor: pointer;"
              @click="oneStepAdminInfo.imageVisible = true; oneStepAdminInfo.index = index"
            />
          </ElCarouselItem>
        </ElCarousel>
        <ElImageViewer
          v-if="oneStepAdminInfo.imageVisible" :url-list="oneStepAdminInfo.data"
          :initial-index="oneStepAdminInfo.index" @close="oneStepAdminInfo.imageVisible = false"
        />
      </FaPageMain> -->

      <FaPageMain class="m-0 flex-1" title-class="flex flex-wrap items-center justify-between gap-4">
        <template #title>
          <div class="title-info">
            <div>
              <h1 class="c-[#67c23a]">
                图书年份统计
              </h1>
            </div>
          </div>
          <div class="ms-auto">
            <FaButton @click="loadBookYearData">
              加载数据
            </FaButton>
          </div>
        </template>
        <div id="book-year-chart" class="chart" />
      </FaPageMain>
    </div>
    <div class="w-full flex flex-col gap-4 px-4 xl-flex-row">
      <FaPageMain class="m-0 flex-1" title-class="flex flex-wrap items-center justify-between gap-4">
        <template #title>
          <div class="title-info">
            <div>
              <h1 class="c-[#67c23a]">
                图书标签统计
              </h1>
            </div>
          </div>
          <div class="ms-auto">
            <FaButton @click="loadBookTagsData">
              加载数据
            </FaButton>
          </div>
        </template>
        <div id="book-tags-chart" class="chart" />
      </FaPageMain>
    </div>
  </div>
</template>

<style scoped>
.text-emphasis {
  text-emphasis-style: "❤";
}

.title-info {
  --uno: flex items-center gap-4;

  img {
    --uno: block w-12 h-12;
  }

  h1 {
    --uno: m-0 text-2xl;
  }

  h2 {
    --uno: m-0 text-base text-secondary-foreground/50 font-normal;
  }
}

.chart {
  --uno: w-full h-[400px];
}
</style>
