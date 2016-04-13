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
	sendMessage( DestinationIP, getNextHop(DestinationIP, fwdTable), encrypt(Message,getReceiverKey(DestinationIP, fwdTable)));
	Message.clear();
	return;
}


int main(int argc, char *argv[]) {
	encryptionInit();

	std::thread routing(start, &fwdTable);
	std::thread test(tcpreceive ,6969, std::ref(q), &fwdTable);

	GtkBuilder *builder;

	std::cout << "Test1" << std::endl;

	gtk_init (&argc, &argv);
	std::cout << "Test1" << std::endl;
	   //Construct a GtkBuilder instance and load our UI description
	builder = gtk_builder_new ();
	gtk_builder_add_from_file (builder, "builder.ui", NULL);

	Button[0] = (GtkButton*) gtk_builder_get_object (builder, "Button1");
	Button[1] = (GtkButton*) gtk_builder_get_object (builder, "Button2");
	Button[2] = (GtkButton*) gtk_builder_get_object (builder, "Button3");
	Button[3] = (GtkButton*) gtk_builder_get_object (builder, "Button4");
	Button[4] = (GtkButton*) gtk_builder_get_object (builder, "Button5");

	Buffer = (GtkTextBuffer*) gtk_builder_get_object(builder, "AllText");
	InputBar = (GtkEntry*) gtk_builder_get_object (builder, "TextInput");
	g_signal_connect (InputBar, "activate", G_CALLBACK (
			Printsend
	), NULL);
	std::cout << "Test1" << std::endl;

	std::cout << "Destination IP" << std::endl;
	std::cin >> DestinationIP;
	gtk_main ();
	std::cout << "Say something: " << std::endl;
	while(1){
		Message.clear();
		std::getline(std::cin, Message);
		if (Message.size()==0){
			Message = getIP() + " is connected to you.";
		}
		sendMessage( DestinationIP, getNextHop(DestinationIP, fwdTable), encrypt(Message,getReceiverKey(DestinationIP, fwdTable)));
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
		const char* lol = IP.c_str();
		if(gtk_button_get_label(Button[i])==lol){
			gtk_button_set_label(Button[i], " ");
		}
	}
}

void addButton(std::string IP){
	for (int i = 0; i<5;i++){
		const char* lol = IP.c_str();
		if(gtk_button_get_label(Button[i])== " "){
			gtk_button_set_label(Button[i], lol);
		}
	}
}
