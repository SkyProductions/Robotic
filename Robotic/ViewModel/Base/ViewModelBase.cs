using System.ComponentModel;

namespace Robotic.ViewModel
{
    public class ViewModelBase : INotifyPropertyChanged
    {
        //basic ViewModelBase
        public void RaisePropertyChanged(string prop)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(prop));
            }
        }
        public event PropertyChangedEventHandler PropertyChanged;

    }


}
