#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"
#include "example_interfaces/srv/trigger.hpp"
#include "example_interfaces/srv/set_bool.hpp"
#include <memory>

void add(const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request,
          std::shared_ptr<example_interfaces::srv::AddTwoInts::Response>      response)
{
  response->sum = request->a + request->b;
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\na: %ld" " b: %ld",
                request->a, request->b);
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%ld]", (long int)response->sum);
}

void trig(const std::shared_ptr<example_interfaces::srv::Trigger::Request> request,
          std::shared_ptr<example_interfaces::srv::Trigger::Response>      response)
{
  response->success = 1;
  response->message = "Successful trigged the service\n";
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\n");
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%d], [%s]\n", (bool)response->success, response->message);
}

void set(const std::shared_ptr<example_interfaces::srv::SetBool::Request> request,
          std::shared_ptr<example_interfaces::srv::SetBool::Response>      response)
{
  response->success = request->data;
  response->message = "Successfull set bool variable of superman to";
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request %d\n", request->data);
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: %s %d\n", response->message, (bool)response->success);
}
int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node_add = rclcpp::Node::make_shared("add_two_ints_server");
  rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr service_add =
    node_add->create_service<example_interfaces::srv::AddTwoInts>("add_two_ints", &add);

  std::shared_ptr<rclcpp::Node> node_trig = rclcpp::Node::make_shared("trigger_server");
  rclcpp::Service<example_interfaces::srv::Trigger>::SharedPtr service_trig =
    node_trig->create_service<example_interfaces::srv::Trigger>("trigger", &trig);

  std::shared_ptr<rclcpp::Node> node_set = rclcpp::Node::make_shared("set_server");
  rclcpp::Service<example_interfaces::srv::SetBool>::SharedPtr service_set =
    node_set->create_service<example_interfaces::srv::SetBool>("set", &set);

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready all three.");
  rclcpp::spin(node_set);
  rclcpp::spin(node_add);
//  TODO loi la do 3 dong nay chi chay 1 dong dau tien
  rclcpp::spin(node_trig);
  rclcpp::shutdown();
}