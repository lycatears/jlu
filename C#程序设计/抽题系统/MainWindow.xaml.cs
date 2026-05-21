using System.Text;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Microsoft.Web.WebView2.Core;
using System.Net.Http.Json;
using System.Security.Policy;
using System.Net.Http.Headers;
using System.Net.Http;
using System.Web;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Globalization;

namespace WpfApp1
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    /// 
    public class QuestionSubstringConverter : IValueConverter
    {
        public int MaxLength { get; set; } = 10;

        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value is string str && !string.IsNullOrEmpty(str))
            {
                str = JsonConvert.DeserializeObject<string>(str);
                var json = JObject.Parse(str);
                return JObject.Parse(str)["problemContent"].ToString().Length > MaxLength ? JObject.Parse(str)["problemContent"].ToString().Substring(0, MaxLength) + "..." : JObject.Parse(str)["problemContent"].ToString();
            }
            return string.Empty;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            return value;
        }
    }

    public partial class MainWindow : Window
    {
        private string apiKey;
        private string apiUrl;
        private string AIModelName;
        private string systemPrompt;
        private string userPrompt;
        private string localLibraryLocation;
        private static HttpClient httpClient = new HttpClient();
        private int timeoutSeconds = 60;
        public MainWindow()
        {
            InitializeComponent();
            string relativeLocation = ".\\ProblemShow\\problemShow.html";
            string absoluteLocation = System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, relativeLocation);
            webView.Source = new Uri(absoluteLocation);

            string configLocation = ".\\ProblemShow\\config.json";
            string config = System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, configLocation);
            JObject configJobject = JObject.Parse(File.ReadAllText(config));
            string? newApiKey = configJobject["APIKey"]?.ToString();
            string? newApiURL = configJobject["URL"]?.ToString();
            string? newLocalLibraryLocation = configJobject["LocalLibraryLocation"]?.ToString();
            string? newAIModelName = configJobject["ModelName"]?.ToString();
            string? newSystemPrompt = configJobject["SystemPrompt"]?.ToString();
            string? newUserPrompt = configJobject["UserPrompt"]?.ToString();

            apiKey = String.IsNullOrEmpty(newApiKey) ? apiKey : newApiKey;
            apiUrl = String.IsNullOrEmpty(newApiURL) ? apiUrl : newApiURL;
            localLibraryLocation = String.IsNullOrEmpty(newLocalLibraryLocation) ? localLibraryLocation : newLocalLibraryLocation;
            AIModelName = String.IsNullOrEmpty(newAIModelName) ? AIModelName : newAIModelName;
            systemPrompt = String.IsNullOrEmpty(newSystemPrompt) ? systemPrompt : newSystemPrompt;
            userPrompt = String.IsNullOrEmpty(newUserPrompt) ? userPrompt : newUserPrompt;
        }

        public void WriteToJsonFile(string[] keys, string[] values)
        {
            string filePath = System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, ".\\ProblemShow\\config.json");

            if (keys == null || values == null)
            {
                throw new ArgumentNullException("keys or values array is null");
            }
            if (keys.Length != values.Length)
            {
                throw new ArgumentException("The length of keys and values must be the same.");
            }

            var jsonObject = new System.Collections.Generic.Dictionary<string, string>();

            for (int i = 0; i < keys.Length; i++)
            {
                jsonObject[keys[i]] = values[i];
            }

            string json = JsonConvert.SerializeObject(jsonObject, Formatting.Indented);

            File.WriteAllText(filePath, json);
        }

        private void StartButton_Click(object sender, RoutedEventArgs e)
        {
            string problemLibLocation = ".\\ProblemShow\\problemLibrary.json";
            string problems = File.ReadAllText(System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, problemLibLocation));
            webView.ExecuteScriptAsync($"initProblems({problems.Trim()});");
        }

        public void setConfig(string apiKey, string apiUrl, string localLibraryLocation, string AIModelName, string systemPrompt, string userPrompt)
        {
            this.apiUrl = apiUrl;
            this.apiKey = apiKey;
            this.localLibraryLocation = localLibraryLocation;
            this.AIModelName = AIModelName;
            this.systemPrompt = systemPrompt;
            this.userPrompt = userPrompt;

            string[] keys = { "URL", "ModelName", "SystemPrompt", "UserPrompt", "APIKey", "LocalLibraryLocation" };
            string[] values = { apiUrl, AIModelName, systemPrompt, userPrompt, apiKey, localLibraryLocation };
            WriteToJsonFile(keys, values);
        }

        private void TimeoutConfig(object sender, RoutedEventArgs e)
        {
            Timeout tmw = new Timeout(timeoutSeconds, this);
            tmw.Show();
        }

        public void setTimeout(int timeout)
        {
            this.timeoutSeconds = timeout;
        }

        private async void AIQuestionButton_Click(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrEmpty(apiKey))
            {
                string noApiKeyMessageTitle = "错误";
                string noApiKeyMessage = "API Key 未设置。请确保已设置您的API Key。\"";
                MessageBox.Show(noApiKeyMessage,
                                noApiKeyMessageTitle,
                                MessageBoxButton.OK,
                                MessageBoxImage.Error);
                return;
            }

            await webView.ExecuteScriptAsync("waitForAIProblem()");

            StringBuilder jsonContent = new StringBuilder();

            string safeSystemPrompt = HttpUtility.JavaScriptStringEncode(systemPrompt);
            string safeUserPrompt = HttpUtility.JavaScriptStringEncode(userPrompt);

            jsonContent.AppendLine("{");
            jsonContent.AppendLine($"  \"model\": \"{AIModelName}\",");
            jsonContent.AppendLine("  \"messages\": [");
            jsonContent.AppendLine("    {");
            jsonContent.AppendLine($"      \"role\": \"system\",");
            jsonContent.AppendLine($"      \"content\": \"{safeSystemPrompt}\"");
            jsonContent.AppendLine("    },");
            jsonContent.AppendLine("    {");
            jsonContent.AppendLine($"      \"role\": \"user\",");
            jsonContent.AppendLine($"      \"content\": \"{safeUserPrompt}\"");
            jsonContent.AppendLine("    }");
            jsonContent.AppendLine("  ]");
            jsonContent.AppendLine("}");

            string resultJson = jsonContent.ToString();
            string result = await SendPostRequestAsync(apiUrl, resultJson, apiKey);

            JObject jObject = JObject.Parse(result);
            var content = jObject["choices"]?[0]?["message"]?["content"]?.ToString();
            string resultProblem = await webView.ExecuteScriptAsync($"setAIProblem({content})");
            //string parsedResult = JsonConvert.DeserializeObject<string>(resultProblem);
            if (resultProblem != null)
            {
                FinishedList.Items.Add(resultProblem);
            }
            await webView.ExecuteScriptAsync($"console.log({result})");

            //MessageBox.Show(result);
        }

        private static async Task<string> SendPostRequestAsync(string url, string jsonContent, string apiKey)
        {
            using (var content = new StringContent(jsonContent, Encoding.UTF8, "application/json"))
            {
                // 设置请求头
                httpClient.DefaultRequestHeaders.Authorization = new AuthenticationHeaderValue("Bearer", apiKey);
                httpClient.DefaultRequestHeaders.Accept.Add(new MediaTypeWithQualityHeaderValue("application/json"));

                // 发送请求并获取响应
                HttpResponseMessage response = await httpClient.PostAsync(url, content);

                // 处理响应
                if (response.IsSuccessStatusCode)
                {
                    return await response.Content.ReadAsStringAsync();
                }
                else
                {
                    return $"请求失败: {response.StatusCode}";
                }
            }
        }

        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {

        }

        private void ProblemLibraryConfig(object sender, RoutedEventArgs e)
        {
            ConfigWindow cfw = new(apiKey, apiUrl, localLibraryLocation, AIModelName, systemPrompt, userPrompt, this);
            cfw.Show();
        }

        private void about(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("面试抽题系统 V1.9 洛樱\n感谢支持", "关于", MessageBoxButton.OK, MessageBoxImage.Information);
        }

        private void ShowKeyButton_Click(object sender, RoutedEventArgs e)
        {
            webView.ExecuteScriptAsync($"showKey();");
        }

        private void SwitchButton_Click(object sender, RoutedEventArgs e)
        {
            webView.ExecuteScriptAsync($"switchToOtherProblem();");
        }

        private void RefreshButton_Click(Object sender, RoutedEventArgs e)
        {
            webView.ExecuteScriptAsync($"refresh();");
            FinishedList.Items.Clear();
        }

        private void MenuItem_Click_1(object sender, RoutedEventArgs e)
        {

        }

        private void ListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (FinishedList.SelectedItem != null)
            {
                string selectedQuestion = FinishedList.SelectedItem.ToString();
                webView.ExecuteScriptAsync($"setProblemObject(JSON.parse({selectedQuestion}))");
            }
        }

        private void Frame_Navigated(object sender, NavigationEventArgs e)
        {

        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {

        }

        private async void NEXTButton_Click(object sender, RoutedEventArgs e)
        {
            string result = await webView.ExecuteScriptAsync("randomProblem();");
            if (result != null && result != "null")
            {
                FinishedList.Items.Add(result);
            }
        }

        private void PREVButton_Click(object sender, RoutedEventArgs e)
        {
            webView.ExecuteScriptAsync("prevProblem();");
        }

        private void Exit_System(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {

        }
    }

    class Problem
    {
        string problemID;
        string subjectName;
        string problemContent;
        string problemKey;
        public Problem(string pID, string sName, string pCon, string pKey)
        {
            this.problemID = pID;
            this.subjectName = sName;
            this.problemContent = pCon;
            this.problemKey = pKey;
        }

        public Problem(string JSONString)
        {
            JObject jObject = JObject.Parse(JSONString);
            this.problemID = jObject["problemID"].ToString();
            this.subjectName = jObject["subjectName"].ToString();
            this.problemContent = jObject["problemContent"].ToString();
            this.problemKey = jObject["problemKey"].ToString();
        }
    }

    
}