using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
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
    }
}
