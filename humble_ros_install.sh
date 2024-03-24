

sudo apt-get update

#install some useful tools
echo "y"| apt-get install vim && echo "y"| apt-get install gedit && echo "y"| apt-get install git


#start to install ros2 foxy
sudo apt update && sudo apt install locales
sudo locale-gen en_US en_US.UTF-8
sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
sudo export LANG=en_US.UTF-8

sudo echo "y" |sudo apt install software-properties-common
sudo echo "y" |sudo add-apt-repository universe

sudo apt update && echo "y" | sudo apt install curl
sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
sudo echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | tee /etc/apt/sources.list.d/ros2.list > /dev/null
sudo apt update
sudo echo "y" | apt install ros-humble-desktop
sudo echo 'source /opt/ros/humble/setup.bash' >> /root/.bashrc

sudo echo "y" | apt install -y python3-pip
pip3 install -U argcomplete

#install colcon 
sudo echo "y" | apt install python3-colcon-common-extensions


