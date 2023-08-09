using Newtonsoft.Json;
using Robotic.Envirement;
using Robotic.Model;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.IO.Packaging;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;
using System.Windows.Input;

namespace Robotic.ViewModel
{
    public class MainViewModel : ViewModelBase
    {

        public ICommand LoginCmd { get; set; }
        public ICommand AddNewProjectCmd { get; set; }

        public MainViewModel()
        {
            LoadProjectsFromJson();

            LoginCmd = new RelayCommand((Object obj) => ViewIndex = 1);
            AddNewProjectCmd = new RelayCommand((Object obj) => ViewIndex = 2);
        }

        void LoadProjectsFromJson()
        {
            string prjsDataPath = EnvirmentHelper.ProjectsDataPath();
            if(File.Exists(prjsDataPath))
            {
                string content = File.ReadAllText(prjsDataPath);
                if(!string.IsNullOrEmpty(content))
                {
                    var projects = JsonConvert.DeserializeObject<List<Project>>(content);

                    foreach(var project in projects)
                    {
                        _projects.Add(new ProjectViewModel()
                        {
                            Id = project.Id,
                            Name = project.Name,
                            Description = project.Description,
                        });
                    }
                }
            }    
        }

        void SaveProjectsToJson()
        {
            string prjsDataPath = EnvirmentHelper.ProjectsDataPath();
            File.WriteAllText(prjsDataPath, JsonConvert.SerializeObject(Projects,Formatting.Indented));
        }

        private int _viewIndex = 0;
        public int ViewIndex
        {
            get => _viewIndex;
            set
            {
                if (_viewIndex != value)
                {
                    _viewIndex = value;
                    RaisePropertyChanged("ViewIndex");
                }
            }
        }


        private ObservableCollection<ProjectViewModel> _projects = new ObservableCollection<ProjectViewModel>();

        public ObservableCollection<ProjectViewModel> Projects
        {
            get => _projects;
            set
            {
                if (_projects != value)
                {
                    _projects = value;
                    RaisePropertyChanged("Projects");
                }
            }
        }
    }
}
