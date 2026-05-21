<template>
    <el-dialog :model-value="visible" title="检测结果" width="80%" @close="$emit('close')">
        <div class="chart-container">
            <div class="chart-item">
                <h3>辱骂攻击</h3>
                <div id="chart-aggressive" style="width: 300px; height: 300px;"></div>
            </div>
            <div class="chart-item">
                <h3>垃圾广告</h3>
                <div id="chart-ad" style="width: 300px; height: 300px;"></div>
            </div>
            <div class="chart-item">
                <h3>低俗色情</h3>
                <div id="chart-porn" style="width: 300px; height: 300px;"></div>
            </div>
            <div class="chart-item">
                <h3>赌博诈骗</h3>
                <div id="chart-fraud" style="width: 300px; height: 300px;"></div>
            </div>
        </div>
    </el-dialog>
</template>

<script>
import { ref, onMounted, watch } from 'vue'
import * as echarts from 'echarts'

export default {
    props: {
        visible: Boolean,
        resultData: Object
    },
    setup(props) {
        const getCategoryName = (key) => {
            const names = {
                aggressive: '辱骂攻击',
                ad: '垃圾广告',
                porn: '低俗色情',
                fraud: '赌博诈骗'
            }
            return names[key] || key
        }

        const renderCharts = () => {
            console.log(props.resultData);

            if (!props.resultData) return

            Object.keys(props.resultData).forEach(key => {
                const chartDom = document.getElementById(`chart-${key}`)
                if (!chartDom) return

                const chart = echarts.init(chartDom)
                const data = props.resultData[key]

                const option = {
                    tooltip: {
                        trigger: 'axis',
                        axisPointer: {
                            type: 'shadow'
                        }
                    },
                    xAxis: {
                        type: 'category',
                        data: ['不符合', '符合']
                    },
                    yAxis: {
                        type: 'value',
                        max: 1,
                        min: 0
                    },
                    series: [
                        {
                            name: '概率',
                            type: 'bar',
                            data: data.probabilities[0],
                            itemStyle: {
                                color: function (params) {
                                    return params.dataIndex === 1 ? '#f56c6c' : '#67c23a'
                                }
                            },
                            label: {
                                show: true,
                                position: 'top',
                                formatter: function (params) {
                                    return (params.value * 100).toFixed(2) + '%'
                                }
                            }
                        }
                    ]
                }

                chart.setOption(option)
            })
        }

        onMounted(() => {
            renderCharts()
        })

        watch(() => props.visible, (newVal) => {
            if (newVal) {
                setTimeout(renderCharts, 100)
            }
        })

        return {
            getCategoryName
        }
    }
}
</script>

<style scoped>
.chart-container {
    display: flex;
    flex-direction: row;
    gap: 40px;
}

.chart-item {
    margin-bottom: 20px;
}

h3 {
    margin-bottom: 15px;
    color: #333;
}
</style>