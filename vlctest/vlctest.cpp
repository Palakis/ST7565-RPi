#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <vlc/vlc.h>

using namespace std;

void metaChanged(const struct libvlc_event_t *event, void *data);
void sigTerm(int signal);

libvlc_instance_t * inst;
libvlc_media_player_t *mp;
libvlc_media_t *m;
libvlc_event_manager_t *mediaEvents;
char *metadata;

int main(int argc, char* argv[])
{
	if(argc <= 1) {
		cout << "URL manquante" << endl;
		return 0;
	}

	signal(SIGINT, &sigTerm);

	inst = libvlc_new(0, NULL);

	m = libvlc_media_new_path(inst, argv[1]);

	mp = libvlc_media_player_new_from_media(m);

	mediaEvents = libvlc_media_event_manager(m);

	libvlc_media_player_play(mp);
	libvlc_event_attach(mediaEvents, libvlc_MediaMetaChanged, &metaChanged, NULL);

	while(1)
	{
	}

	return 0;
}

void metaChanged(const struct libvlc_event_t* event, void* data)
{
	libvlc_meta_t metaType = event->u.media_meta_changed.meta_type;
	libvlc_media_t *pMedia = (libvlc_media_t*) data;
	cout << "Metadonnées reçues pour la clé " << metaType << endl;
	libvlc_media_parse(m);
	cout << "Données: " << libvlc_media_get_meta(m, metaType) << endl;

}

void sigTerm(int signal)
{
	cout << "SIGTERM reçu" << endl;
	libvlc_media_player_stop(mp);
	libvlc_media_player_release(mp);
	libvlc_release(inst);
	exit(0);
}
