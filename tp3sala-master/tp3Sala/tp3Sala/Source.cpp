#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <iostream>

using namespace std;

bool Collision(int pX, int pY, int eX, int eY, int pWidth, int pHeight, int eWidth, int eHeight) {
	if (pX + pWidth<eX || pX > eX + eWidth || pY + pHeight < eY || pY > eY + eHeight) {
		return false;
	}
	else {
		return true;
	}
}

int main(int argc, char **argv){


	ALLEGRO_DISPLAY * display;
	ALLEGRO_EVENT_QUEUE *queue;
	ALLEGRO_BITMAP * playerBitmap = NULL;
	ALLEGRO_BITMAP *enemieBitmap = NULL;
	ALLEGRO_BITMAP *enemie2Bitmap = NULL;

	al_init();

	const int displayWidth = 800;
	const int displayHeight = 600;

	display = al_create_display(displayWidth, displayHeight);
	queue = al_create_event_queue();

	al_install_keyboard();
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_init_image_addon();

	playerBitmap = al_load_bitmap("Blue_01.png");
	enemieBitmap = al_load_bitmap("Blue_01.png");
	enemie2Bitmap = al_load_bitmap("Blue_01.png");

	bool running = true;

	float widthPlayerBitmap = al_get_bitmap_width(playerBitmap);
	float heightPlayerBitmap = al_get_bitmap_height(playerBitmap);

	float widthEnemieBitmap = al_get_bitmap_width(enemieBitmap);
	float heightEnemieBitmap = al_get_bitmap_height(enemieBitmap);

	float widthEnemie2Bitmap = al_get_bitmap_width(enemieBitmap);
	float heightEnemie2Bitmap = al_get_bitmap_height(enemieBitmap);

	float initialPlayerX = 0;
	float initialPlayerY = (displayHeight / 2) - heightPlayerBitmap;
	float playerX = initialPlayerX;
	float playerY = initialPlayerY;

	float enemieX = 400;
	float enemieY = 400;

	float enemie2X = 300;
	float enemie2Y = 0;

	float velocity = 4.5f;

	cout << "width bitmap 1" << widthPlayerBitmap<<endl;
	cout << "height bitmap 1" << heightPlayerBitmap << endl;

	while (running) {
		al_clear_to_color(al_map_rgba_f(1, 1, 1, 1));
		al_draw_bitmap(playerBitmap, playerX,playerY, 0);
		al_draw_bitmap(enemieBitmap, enemieX, enemieY, 0);
		al_draw_bitmap(enemie2Bitmap, enemie2X, enemie2Y, 0);
		al_flip_display();

		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			running = false;
	
		ALLEGRO_KEYBOARD_STATE keyState;
		al_get_keyboard_state(&keyState);
		if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
		{
			playerX += velocity;
		}	
		if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
		{
			playerX -= velocity;
		}
		if (al_key_down(&keyState, ALLEGRO_KEY_UP)) {
			playerY -= velocity;
		}
		if (al_key_down(&keyState, ALLEGRO_KEY_DOWN)) {
			playerY += velocity;
		}

		cout << "posx1 " << playerX << endl;
		cout << "posx2 " << enemieX << endl;

		if (Collision(playerX, playerY, enemieX, enemieY, widthPlayerBitmap, heightPlayerBitmap, widthEnemieBitmap, heightEnemieBitmap) || Collision(playerX, playerY, enemie2X, enemie2Y, widthPlayerBitmap, heightPlayerBitmap, widthEnemie2Bitmap, heightEnemie2Bitmap)) {
			cout << "contacto" << endl;
			running = false;
		}
	}

	al_destroy_display(display);
	al_uninstall_keyboard();
	al_destroy_bitmap(playerBitmap);
	al_destroy_bitmap(enemieBitmap);

	return 0;
}