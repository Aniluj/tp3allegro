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
	ALLEGRO_BITMAP * playerBitmap = NULL;
	ALLEGRO_BITMAP *enemieBitmap = NULL;
	ALLEGRO_BITMAP *enemie2Bitmap = NULL;

	al_init();

	const float fps = 60.0;
	const int displayWidth = 800;
	const int displayHeight = 600;

	display = al_create_display(displayWidth, displayHeight);

	al_install_keyboard();
	al_init_image_addon();

	playerBitmap = al_load_bitmap("Blue_01.png");
	enemieBitmap = al_load_bitmap("Blue_01.png");
	enemie2Bitmap = al_load_bitmap("Blue_01.png");

	bool running = true;

	float widthPlayerBitmap = al_get_bitmap_width(playerBitmap);
	float heightPlayerBitmap = al_get_bitmap_height(playerBitmap);

	bool enemieGoingUp = false;
	float widthEnemieBitmap = al_get_bitmap_width(enemieBitmap);
	float heightEnemieBitmap = al_get_bitmap_height(enemieBitmap);

	bool enemie2GoingRight = false;
	float widthEnemie2Bitmap = al_get_bitmap_width(enemieBitmap);
	float heightEnemie2Bitmap = al_get_bitmap_height(enemieBitmap);

	int playerLife = 3;
	float initialPlayerX = 0;
	float initialPlayerY = (displayHeight / 2) - heightPlayerBitmap;
	float playerX = initialPlayerX;
	float playerY = initialPlayerY;

	float enemieX = 400;
	float enemieY = 400;
	float enemieMovementSpeed = 5.0f;

	float enemie2X = 300;
	float enemie2Y = 0;
	float enemie2MovementSpeed = 5.0f;

	float playerMovementSpeed = 4.5f;

	cout << "width bitmap 1" << widthPlayerBitmap<<endl;
	cout << "height bitmap 1" << heightPlayerBitmap << endl;

	ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();;
	ALLEGRO_KEYBOARD_STATE keyState;
	ALLEGRO_TIMER *timer = al_create_timer(1.0 / fps);
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));

	al_start_timer(timer);

	while (running){

		ALLEGRO_EVENT events;
		al_wait_for_event(queue, &events);

		al_clear_to_color(al_map_rgba_f(1, 1, 1, 1));
		al_draw_bitmap(playerBitmap, playerX,playerY, 0);
		al_draw_bitmap(enemieBitmap, enemieX, enemieY, 0);
		al_draw_bitmap(enemie2Bitmap, enemie2X, enemie2Y, 0);
		al_flip_display();

		if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			running = false;

		if (events.type == ALLEGRO_EVENT_TIMER){

			al_get_keyboard_state(&keyState);
			if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
			{
				playerX += playerMovementSpeed;
			}
			if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
			{
				playerX -= playerMovementSpeed;
			}
			if (al_key_down(&keyState, ALLEGRO_KEY_UP)) {
				playerY -= playerMovementSpeed;
			}
			if (al_key_down(&keyState, ALLEGRO_KEY_DOWN)) {
				playerY += playerMovementSpeed;
			}

			cout << "posx1 " << playerX << endl;
			cout << "posx2 " << enemieX << endl;

			if (Collision(playerX, playerY, enemieX, enemieY, widthPlayerBitmap, heightPlayerBitmap, widthEnemieBitmap, heightEnemieBitmap) || Collision(playerX, playerY, enemie2X, enemie2Y, widthPlayerBitmap, heightPlayerBitmap, widthEnemie2Bitmap, heightEnemie2Bitmap)) {
				cout << "contacto" << endl;
				running = false;
			}

			if (!enemieGoingUp) {
				enemieY += enemieMovementSpeed;
			}
			if (enemieGoingUp) {
				enemieY -= enemieMovementSpeed;
			}
			if (enemieY + heightEnemieBitmap >= displayHeight) {
				enemieGoingUp = true;
			}
			else if (enemieY <= 0) {
				enemieGoingUp = false;
			}

			if (!enemie2GoingRight) {
				enemie2X += enemie2MovementSpeed;
			}
			else {
				enemie2X -= enemie2MovementSpeed;
			}
			if (enemie2X + widthEnemie2Bitmap >= displayWidth) {
				enemie2GoingRight = true;
			}
			else if (enemie2X <= 0) {
				enemie2GoingRight = false;
			}
		}
	}

	al_destroy_display(display);
	al_uninstall_keyboard();
	al_destroy_bitmap(playerBitmap);
	al_destroy_bitmap(enemieBitmap);
	al_destroy_bitmap(enemie2Bitmap);
	al_destroy_timer(timer);

	return 0;
}