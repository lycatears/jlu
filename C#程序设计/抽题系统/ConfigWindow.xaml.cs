using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace WpfApp1
{
    /// <summary>
    /// Window1.xaml 的交互逻辑
    /// </summary>
    public partial class ConfigWindow : Window
    {
        MainWindow mw;
        private string apiKey = "";
        private string apiUrl = "";
        private string AIModelName = "";
        private string systemPrompt = "";
        private string userPrompt = "";
        private string localLibraryLocation = "";
        public ConfigWindow(string apiKey, string apiUrl, string localLibraryLocation, string AIModelName, string systemPrompt, string userPrompt, MainWindow mw)
        {
            InitializeComponent();
            this.apiUrl=URLTextBox.Text = apiUrl;
            this.apiKey=APIKeyTextBox.Text = apiKey;
            this.localLibraryLocation = LocalLibraryTextBox.Text = localLibraryLocation;
            this.AIModelName = AIModelNameTextBox.Text = AIModelName;
            this.systemPrompt = SystemPromptTextBox.Text = systemPrompt;
            this.userPrompt = UserPromptTextBox.Text = userPrompt;
            this.mw = mw;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            mw.setConfig(APIKeyTextBox.Text, URLTextBox.Text, LocalLibraryTextBox.Text, AIModelNameTextBox.Text, SystemPromptTextBox.Text, UserPromptTextBox.Text);
            this.Close();
        }
    }
}
