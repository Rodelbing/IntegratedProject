//GUI? zie SFML
#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <thread>
#include <cstring>
#include <unistd.h>
#include <vector>
#include "lib/Includes.h"
#include "network/getIP.h"
#include "network/multisend.h"
#include "network/multisend.h"
#include "network/tcpsend.h"
#include "network/tcpreceive.h"
#include "lib/BlockingQueue.h"
#include "network/multireceive.h"
#include "network/sendMessage.h"
#include "network/distancevector.h"
#include "encryption/encryption.h"

static BlockingQueue<std::string> q;
vector<tableEntry> fwdTable;

GtkTextBuffer *Buffer;
GtkEntry *InputBar;
GtkButton *Button[5];

std::string DestinationIP;
std::string MyIP = getIP();
std::string Message;

void Printsend(GtkMenuItem *sender, gpointer user_data)
{
	const gchar *Input = gtk_entry_get_text (InputBar);
	std::string Message = (std::string) Input;
	std::string Print = "You: " + Message + "\n";
	const gchar *Insert = &Print[0];
	gtk_text_buffer_insert_at_cursor(Buffer, Insert , -1);

	gtk_entry_set_text(InputBar, "");
	if (Message.size()==0){
		Message = getIP() + " is connected to you.";
	}
	if (DestinationIP.size()!=0){
		sendMessage(getIP(), DestinationIP, getNextHop(DestinationIP, fwdTable), encrypt(Message,getReceiverKey(DestinationIP, fwdTable)));
	}
	Message.clear();
	return;
}

void ButtonClick(GtkButton *sender, gpointer user_data)
{
	cout << gtk_button_get_label(sender) << endl;
	if(gtk_button_get_label(sender) != "NONE"){
		DestinationIP = gtk_button_get_label(sender);
	}

	return;
}


int main(int argc, char *argv[]) {
	encryptionInit();

	std::thread routing(start, &fwdTable);
	std::thread test(tcpreceive ,6969, std::ref(q), &fwdTable);

	GtkBuilder *builder;

	std::cout << "Test1" << std::endl;

	gtk_init (&argc, &argv);
	   //Construct a GtkBuilder instance and load our UI description
	builder = gtk_builder_new ();
	gtk_builder_add_from_file (builder, "builder.ui", NULL);

	Button[0] = (GtkButton*) gtk_builder_get_object (builder, "button1");
	Button[1] = (GtkButton*) gtk_builder_get_object (builder, "button2");
	Button[2] = (GtkButton*) gtk_builder_get_object (builder, "button3");
	Button[3] = (GtkButton*) gtk_builder_get_object (builder, "button4");
	Button[4] = (GtkButton*) gtk_builder_get_object (builder, "button5");
	g_signal_connect (Button[0], "clicked", G_CALLBACK (ButtonClick), NULL);
	g_signal_connect (Button[1], "clicked", G_CALLBACK (ButtonClick), NULL);
	g_signal_connect (Button[2], "clicked", G_CALLBACK (ButtonClick), NULL);
	g_signal_connect (Button[3], "clicked", G_CALLBACK (ButtonClick), NULL);
	g_signal_connect (Button[4], "clicked", G_CALLBACK (ButtonClick), NULL);

	Buffer = (GtkTextBuffer*) gtk_builder_get_object(builder, "AllText1");
	InputBar = (GtkEntry*) gtk_builder_get_object (builder, "TextInput");
	g_signal_connect (InputBar, "activate", G_CALLBACK (Printsend), NULL);

	//std::cout << "Destination IP" << std::endl;
	//std::cin >> DestinationIP;
	gtk_main ();
	std::cout << "Say something: " << std::endl;
	while(1){
		Message.clear();
		std::getline(std::cin, Message);
		if (Message.size()==0){
			Message = getIP() + " is connected to you.";
		}
		sendMessage(getIP(), DestinationIP, getNextHop(DestinationIP, fwdTable), encrypt(Message,getReceiverKey(DestinationIP, fwdTable)));
		//string Hoi = encrypt(Message,getPublicKey());
		//std:: cout << Hoi << ", " << decrypt(Hoi, getPublicKey()) << std::endl;
		//std::cout << getNextHop(DestinationIP) << std::endl;
	}

}

void incomingMessage(string input){
	const char* message = input.c_str();
	gtk_text_buffer_insert_at_cursor(Buffer, message , -1);
}

void deleteButton(std::string IP){
	for (int i = 0; i<5;i++){
		std::string ButtonString = (std::string) gtk_button_get_label(Button[i]);
		if(IP==ButtonString){
			gtk_button_set_label(Button[i], "NONE");
			if(DestinationIP == ButtonString){
				DestinationIP = "";
			}
		}
	}
}

void addButton(std::string IP){
	cout << IP << endl;
	for (int i = 0; i<5;i++){
		const char* lol = IP.c_str();

		std::string ButtonString = (std::string) gtk_button_get_label(Button[i]);
		cout << ButtonString << endl;
		if(ButtonString=="NONE"){
			cout << "Hoi" << endl;
			gtk_button_set_label(Button[i], lol);
			return;
		}
	}
}
