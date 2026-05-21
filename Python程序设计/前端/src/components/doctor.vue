<template>
    <div class="veterinary-form">
        <div class="form-actions">
            <el-button type="primary" @click="submitForm">提交表单</el-button>
            <el-button @click="resetForm">重置表单</el-button>
        </div>
        <el-tabs v-model="activePage" type="card">
            <el-tab-pane v-for="(page, pageIndex) in formData" :key="pageIndex"
                :label="page.title || `第${pageIndex + 1}页`">
                <div class="page-content">
                    <el-card v-for="(card, cardIndex) in page.cards" :key="cardIndex" class="card-item">
                        <template #header v-if="card.name">
                            <div class="card-header">{{ card.name }}</div>
                        </template>
                        <div class="problems-container">
                            <div v-for="(problem, problemIndex) in card.problems" :key="problemIndex"
                                class="problem-item">
                                <div class="problem-label">{{ problem.name }}</div>

                                <!-- 文本输入框 -->
                                <el-input v-if="problem.type === 'text'"
                                    v-model="formValues[pageIndex][cardIndex][problemIndex]"
                                    :placeholder="problem.placeholder || ''" clearable />

                                <!-- 数字输入框 -->
                                <el-input v-else-if="problem.type === 'number'"
                                    v-model.number="formValues[pageIndex][cardIndex][problemIndex]"
                                    :placeholder="problem.placeholder || ''" type="number" clearable />

                                <!-- 单选题 -->
                                <el-radio-group v-else-if="problem.type === 'singleChoice'"
                                    v-model="formValues[pageIndex][cardIndex][problemIndex]">
                                    <el-radio-button v-for="option in problem.options" :key="option.value"
                                        :label="option.value" size="small">
                                        {{ option.label }}
                                    </el-radio-button>
                                </el-radio-group>

                                <!-- 多选题 -->
                                <el-checkbox-group
                                    v-else-if="problem.type === 'multipleChoice' || problem.type === 'mulipleChoice'"
                                    v-model="formValues[pageIndex][cardIndex][problemIndex]">
                                    <el-checkbox-button v-for="option in problem.options" :key="option.value"
                                        :label="option.value" size="small">
                                        {{ option.label }}
                                    </el-checkbox-button>
                                </el-checkbox-group>
                            </div>
                        </div>
                    </el-card>
                </div>
            </el-tab-pane>
        </el-tabs>
    </div>
</template>

<script>
import formData from './questions.json';

export default {
    name: 'VeterinaryForm',
    data() {
        // 初始化表单值结构
        const initFormValues = () => {
            return formData.map(page =>
                page.cards.map(card =>
                    card.problems.map(problem => {
                        if (problem.type === 'multipleChoice' || problem.type === 'mulipleChoice') {
                            return [];
                        }
                        return '';
                    })
                )
            );
        };

        return {
            formData,
            activePage: 0,
            formValues: initFormValues()
        };
    },
    methods: {
        submitForm() {
            // 这里可以处理表单提交逻辑
            console.log('表单数据:', this.formValues);
            this.$message.success('表单提交成功！');

            // 实际应用中，这里可以发送数据到后端
            // axios.post('/api/submit', this.formValues).then(...)
        },
        resetForm() {
            // 重置表单
            this.formValues = this.formData.map(page =>
                page.cards.map(card =>
                    card.problems.map(problem => {
                        if (problem.type === 'multipleChoice' || problem.type === 'mulipleChoice') {
                            return [];
                        }
                        return '';
                    })
                )
            );
            this.$message.info('表单已重置');
        }
    }
};
</script>

<style scoped>
.veterinary-form {
    padding: 20px;
}

.page-content {
    display: flex;
    flex-direction: column;
    gap: 20px;
}

.card-item {
    margin-bottom: 20px;
}

.card-header {
    font-weight: bold;
    font-size: 16px;
}

.problems-container {
    display: flex;
    flex-direction: column;
    gap: 15px;
}

.problem-item {
    display: flex;
    flex-direction: column;
    gap: 8px;
}

.problem-label {
    font-weight: 500;
    margin-bottom: 5px;
}

.form-actions {
    margin-top: 20px;
    text-align: center;
}

/* 调整单选和多选按钮组的样式 */
.el-radio-group,
.el-checkbox-group {
    display: flex;
    flex-wrap: wrap;
    /*gap: 8px;*/
}
</style>