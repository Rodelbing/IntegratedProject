//GUI? zie SFML
#include <gtk/gtk.h>
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

void Printsend(GtkMenuItem *sender, gpointer user_data)
{
	const gchar *Input = gtk_entry_get_text (InputBar);
	gtk_text_buffer_insert_at_cursor(Buffer, Input , -1);
	gtk_entry_set_text(InputBar, "");

			return;
}


int main(int argc, char *argv[]) {
	std::string DestinationIP;
	std::string MyIP = getIP();
	std::string Message;
	std::thread routing(start, &fwdTable);
	std::thread test(tcpreceive ,6969, std::ref(q), &fwdTable);
	encryptionInit();

	GtkBuilder *builder;
	GObject *window;
	GObject *ChatWindow;


	gtk_init (&argc, &argv);

	   //Construct a GtkBuilder instance and load our UI description
	builder = gtk_builder_new ();
	gtk_builder_add_from_file (builder, "builder.ui", NULL);

	Buffer = (GtkTextBuffer*) gtk_builder_get_object(builder, "AllText");
	gtk_text_buffer_set_text(Buffer, "Hoi " , -1);
	InputBar = (GtkEntry*) gtk_builder_get_object (builder, "TextInput");
	ChatWindow = gtk_builder_get_object (builder, "ChatText");
	g_signal_connect (InputBar, "activate", G_CALLBACK (
			Printsend
	), NULL);


	std::cout << "Destination IP" << std::endl;
	std::cin >> DestinationIP;
	std::cout << "Say something: " << std::endl;
	while(1){
		Message.clear();
		std::getline(std::cin, Message);
		if (Message.size()==0){
			Message = getIP() + " is connected to you.";
		}
		sendMessage( DestinationIP, getNextHop(DestinationIP, fwdTable), encrypt(Message,getPublicKey()));
		//string Hoi = encrypt(Message,getPublicKey());
		//std:: cout << Hoi << ", " << decrypt(Hoi, getPublicKey()) << std::endl;
		//std::cout << getNextHop(DestinationIP) << std::endl;
	}

}


