#include <iostream>
#include <string>

using namespace std;

// Something to hold packets of info
struct Packet {
    int msg_number;       // Which message this belongs to
    int packet_number;    // Which part of the message
    char data;            // The actual data (one char)
    Packet* next;         // Next packet in the list
};

// A list that handles all the packets
class PacketList {
private:
    Packet* head;         // Start of the list
    Packet* tail;         // End of the list
    int current_msg_num;  // Current message number we're on

public:
    // Setting up the list
    PacketList() : head(nullptr), tail(nullptr), current_msg_num(1) {}

    // When done, clear everything
    ~PacketList() {
        clear();
    }

    // Break down a message into packets
    void decomposeMessage(const string& message) {
        int packet_number = 1;  // Start counting packets

        // Loop through each character in the message
        for (char ch : message) {
            Packet* newNode = new Packet();  // Make a new packet
            newNode->msg_number = current_msg_num;
            newNode->packet_number = packet_number++;
            newNode->data = ch;
            newNode->next = nullptr;

            // If it's the first packet, set head and tail
            if (head == nullptr) {
                head = newNode;
                tail = newNode;
            } else {
                // Otherwise, add to the end
                tail->next = newNode;
                tail = newNode;
            }
        }
        current_msg_num++;  // Move to the next message
    }

    // Show everything in the list
    void display_list() const {
        Packet* temp = head;
        int total_packets = 0;  // Keep track of the total packets

        // Loop through the list
        while (temp != nullptr) {
            cout << "The value of packet " << temp->packet_number 
                 << " in message " << temp->msg_number 
                 << " is " << temp->data << endl;
            temp = temp->next;
            total_packets++;  // Counting packets
        }
        cout << "The total packets in the linked list are " << total_packets << endl;
    }

    // Clean up all the packets
    void clear() {
        Packet* temp;
        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;  // Reset the tail too
    }
};

// Main function to try it all out
int main() {
    PacketList p;

    // Break down some messages into packets
    p.decomposeMessage("Hello");
    p.decomposeMessage("This");
    p.decomposeMessage("is");
    p.decomposeMessage("CS221");
    p.decomposeMessage("Assignment");

    // Show all the packets
    cout << "Displaying all packets" << endl;
    p.display_list();

    return 0;
}
