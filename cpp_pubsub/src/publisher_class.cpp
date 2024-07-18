#include "publisher_class.hpp"

using namespace std::chrono_literals;

publisher_class::publisher_class(): Node("publisher_node")
{
    publisher_ = this->create_publisher<std_msgs::msg::Float32>("topic_float", 10);
    publisher_2 = this->create_publisher<std_msgs::msg::Bool>("topic_bool",10);
    timer_ = this->create_wall_timer(std::chrono::milliseconds(1000), std::bind(&publisher_class::callback_, this));
    timer_2 = this->create_wall_timer(700ms, std::bind(&publisher_class::callback_2,this));

}
void publisher_class::callback_()
{
    auto number = std_msgs::msg::Float32();
    number.data = send_number;
    RCLCPP_INFO(this->get_logger(), "Publishing no2: '%.2f'", number.data);
    publisher_->publish(number);
    send_number++;
}
void publisher_class::callback_2() 
{
    auto state = std_msgs::msg::Bool();
    state.data = tr;
    RCLCPP_INFO(this->get_logger(), "Publishing state of tr: '%.2d'", state.data);
    publisher_2->publish(state);
    //tr = !tr;
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<publisher_class>());
  rclcpp::shutdown();
  return 0;
}