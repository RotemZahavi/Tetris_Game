#ifndef __GAME_CONFIG_H
#define __GAME_CONFIG_H


class GameConfig
{
public:

	enum class eKeys {
		LEFT_A = 'a', RIGHT_A = 'd', ESC = 27, ROTATE_CLOCKWISE_A = 's', ROTATE_COUNTER_CLOCKWISE_A = 'w', DROP_A = 'x',
		LEFT_B = 'j', RIGHT_B = 'l', ROTATE_CLOCKWISE_B = 'k', ROTATE_COUNTER_CLOCKWISE_B = 'i', DROP_B = 'm', ENTER = 13
	};

	static constexpr int SHAPE_SIZE = 4;
	static constexpr int KBHIT_ROUNDS = 10;

	static constexpr int GAME_WIDTH = 12;
	static constexpr int GAME_HEIGHT = 18;

	static constexpr int MIN_X = 1;
	static constexpr int MIN_Y = 1;
	static constexpr int OFFSET = 20;
	static constexpr int OFFSET_0 = 0;

	void drawBoards() const;
};

#endif

