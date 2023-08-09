using Robotic.Envirement;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Input;

namespace Robotic.ViewModel
{
    public class ProjectViewModel : ViewModelBase
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public string Unit { get; set; }
        public string Description { get; set; }

        public ICommand saveProjctCmd { get; set; }
        public ICommand viewProjctCmd { get; set; }


        public ProjectViewModel()
        {
            viewProjctCmd = new RelayCommand(viewProjctInvoke);
        }

        private void viewProjctInvoke(object obj)
        {
            OpenFileDialog openFileDialog1 = new OpenFileDialog
            {
                InitialDirectory = @"D:\",
                Title = "Browse Step Files",

                CheckFileExists = true,
                CheckPathExists = true,

                DefaultExt = "step",
                Filter = "Step files (*.stp)|*.stp|(*.step)|*.step",
                FilterIndex = 2,
                RestoreDirectory = true,

                ReadOnlyChecked = true,
                ShowReadOnly = true
            };

            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                //Convert then copy file to folder
                string devicesFolder = EnvirmentHelper.GlobalDevicesFolder();
                string destFile = Path.Combine(devicesFolder,Path.GetFileName(openFileDialog1.FileName));
                File.Copy(openFileDialog1.FileName, destFile);
            }
        }
    }
}
