#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float32.hpp>
#include <std_msgs/msg/bool.hpp>

class publisher_class : public rclcpp::Node
{
    public:
        publisher_class();
        void callback_();
        void callback_2();
    private:
        rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr publisher_;
        rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr publisher_2;
        rclcpp::TimerBase::SharedPtr timer_;
        rclcpp::TimerBase::SharedPtr timer_2;
        float send_number= 69;
        bool tr = true;
        
};