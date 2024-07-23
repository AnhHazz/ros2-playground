#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/srv/add_two_ints.hpp>
#include "example_interfaces/srv/trigger.hpp"
#include "example_interfaces/srv/set_bool.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;


int main(int argc, char **argv) 
{
    rclcpp::init(argc, argv);
    
    if(argc == 1) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "send to trigger server");
        std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("trigger_client");
        rclcpp::Client<example_interfaces::srv::Trigger>::SharedPtr client = 
        node->create_client<example_interfaces::srv::Trigger>("trigger");

        auto request = std::make_shared<example_interfaces::srv::Trigger::Request>();

        while (!client->wait_for_service(1s))
          {
              if(!rclcpp::ok()) 
              {
                  RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupt while waiting for service");
                  return 0;
              }
              RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");

          }
          auto result = client->async_send_request(request);

            if (rclcpp::spin_until_future_complete(node, result) ==
          rclcpp::FutureReturnCode::SUCCESS)
        {
          RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "trigger %s", result.get()->message);
        } else {
          RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service trigger");
        }
    }
    else if(argc == 3){
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "send to add two ints server");
      std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_two_ints_client");
      rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client = 
      node->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");

      auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
      request->a = atoll(argv[1]);
      request->b = atoll(argv[2]);

      while (!client->wait_for_service(1s))
        {
            if(!rclcpp::ok()) 
            {
                RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupt while waiting for service");
                return 0;
            }
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting agin...");

        }
        auto result = client->async_send_request(request);

          if (rclcpp::spin_until_future_complete(node, result) ==
        rclcpp::FutureReturnCode::SUCCESS)
      {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Sum: %ld", result.get()->sum);
      } else {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service add_two_ints");
      }

    }

    else if(argc == 2){
      std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("set_client");
      rclcpp::Client<example_interfaces::srv::SetBool>::SharedPtr client = 
      node->create_client<example_interfaces::srv::SetBool>("set");

      auto request = std::make_shared<example_interfaces::srv::SetBool::Request>();
      request->data = (bool)(argv[1]);

      while (!client->wait_for_service(1s))
      {
          if(!rclcpp::ok()) 
          {
              RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupt while waiting for service");
              return 0;
          }
          RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting agin...");

      }
      auto result = client->async_send_request(request);

        if (rclcpp::spin_until_future_complete(node, result) ==
      rclcpp::FutureReturnCode::SUCCESS)
    {
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "set bool: %s", result.get()->message);
    } else {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service set bool");
    }
      }
    else 
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "No server match your argument list");
      
  rclcpp::shutdown();
  return 0;
}