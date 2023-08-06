using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
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
            _projects.Add(new ProjectViewModel()
            {
                Id = 0,
                Name = "Project 1",
                Description = "Description 1",
            });

            _projects.Add(new ProjectViewModel()
            {
                Id = 1,
                Name = "Project 2",
                Description = "Description 2",
            });


            LoginCmd = new RelayCommand((Object obj) => ViewIndex = 1);
            AddNewProjectCmd = new RelayCommand((Object obj) => ViewIndex = 2);
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
