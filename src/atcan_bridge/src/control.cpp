#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include "std_msgs/msg/u_int16_multi_array.hpp"
#include <vector>
#include <iostream>

class ControlNode : public rclcpp::Node
{
public:
    ControlNode() : Node("control_node")
    {
        pub_bridge = this->create_publisher<std_msgs::msg::String>("atcan_tx", 10);
        sub_bridge = this->create_subscription<std_msgs::msg::String>("atcan_rx", 10,
            std::bind(&ControlNode::bridge_callback, this, std::placeholders::_1));
        pub_master = this->create_publisher<std_msgs::msg::String>("observe_tx", 10);
        sub_master = this->create_subscription<std_msgs::msg::UInt16MultiArray>("observe_rx", 10,
            std::bind(&ControlNode::master_callback, this, std::placeholders::_1));
    }

private:
    void bridge_callback(const std_msgs::msg::String::SharedPtr msg)
    {
        std_msgs::msg::String res_msg;
        auto forward_msg = std_msgs::msg::String();
        forward_msg.data = msg->data;
        res_msg = compare(2, forward_msg);
        pub_master->publish(res_msg);
    }

    void master_callback(const std_msgs::msg::UInt16MultiArray::SharedPtr msg)
    {
        auto mode = uint8_t((msg->data)[1] & 0xFF);
        std_msgs::msg::String can_msg;

        switch (mode)
        {
        case 0x01: // MIT mode
            can_msg = build_mit_can(std::vector<uint16_t>(msg->data));
            compare(1, can_msg);
            break;
        case 0x12: // setting mode
            break;
        }
        pub_bridge->publish(can_msg);
    }

    static inline std_msgs::msg::String
    compare(int mode, const std_msgs::msg::String& can_msg) {
        static std_msgs::msg::String target_msg;
        static std_msgs::msg::String judge;
        std_msgs::msg::String result_msg;

        if (mode == 1) {
            target_msg.data = can_msg.data;
            judge.data = can_msg.data.substr(0, 1);
            judge.data += can_msg.data.substr(9, 12);
            result_msg.data = "Target message set.";
        } else if (mode == 2) {
            string received = can_msg.data.substr(4, 5)
            received += can_msg.data.substr(9, 12);
            if (received == target_msg.data) {
                result_msg.data = "goal";
            } else {

                result_msg.data = "wait";
                pub_bridge->publish(target_msg);
            }
        } else {
            result_msg.data = "Unknown mode.";
        }
        return result_msg;
    }

    static inline std_msgs::msg::String
    build_mit_can(const std::vector<uint16_t>& data)
    {
        std_msgs::msg::String msg;
        static constexpr char HEX[] = "0123456789ABCDEF";

        // 最低でも id(=data[0]) と torque(=data[2]) を読むならサイズ確認
        if (data.size() < 3) {
            msg.data = "";  // or エラーメッセージ
            return msg;
        }

        auto push_byte_hex = [&](uint8_t b) {
            msg.data.push_back(HEX[(b >> 4) & 0x0F]);
            msg.data.push_back(HEX[(b     ) & 0x0F]);
        };
        auto push_word_hex = [&](uint16_t v) {          // MSB→LSB の4桁
            msg.data.push_back(HEX[(v >> 12) & 0x0F]);
            msg.data.push_back(HEX[(v >>  8) & 0x0F]);
            msg.data.push_back(HEX[(v >>  4) & 0x0F]);
            msg.data.push_back(HEX[(v      ) & 0x0F]);
        };

        // だいたいの長さを見積もって予約（再確保を減らす）
        const std::size_t payload_words = (data.size() > 3) ? (data.size() - 3) : 0;
        msg.data.reserve(2 /*01*/ + 2 /*torque*/ + 2 /*FD*/ + 2 /*id*/ +
                        (payload_words ? 1 : 0) /*#*/ + payload_words * 4);

        // ヘッダ部（1回だけ）
        msg.data += "01";
        push_byte_hex(static_cast<uint8_t>(data[2] & 0x00FF));  // torque: 下位8bit
        msg.data += "FD";
        push_byte_hex(static_cast<uint8_t>(data[0] & 0x00FF));  // id: 下位8bit

        // ペイロード（あれば）
        if (payload_words > 0) {
            msg.data.push_back('#');
            for (std::size_t i = 3; i < data.size(); ++i) {
                push_word_hex(data[i]);                          // 16bit → 4桁HEX
                // 区切りが必要ならここで ' ' などを push_back
            }
            }

        // 末尾に CRLF が要るプロトコルなら:  msg.data += "\r\n";
        return msg;
    }


    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_bridge;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_bridge;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_master;
    rclcpp::Subscription<std_msgs::msg::UInt16MultiArray>::SharedPtr sub_master;       
};