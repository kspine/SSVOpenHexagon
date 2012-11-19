#ifndef HEXAGONGAME_H_
#define HEXAGONGAME_H_

#include <map>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <json/json.h>
#include <json/reader.h>
#include <SSVStart.h>
#include <SSVEntitySystem.h>
#include "Data/LevelData.h"
#include "Data/MusicData.h"
#include "Data/StyleData.h"

using namespace sf;
using namespace ssvs;
using namespace sses;

namespace hg
{
	class MenuGame;
	class PatternManager;

	class HexagonGame
	{
		friend class PatternManager;

		private:
			Game game;
			GameWindow& window;
			Manager manager;
			RenderTexture gameTexture;
			Sprite gameSprite;

			LevelData levelData;
			MusicData musicData;
			StyleData styleData;
			Music* musicPtr{nullptr};

			PatternManager* pm; // owned, opaque pointer
			Timeline timeline;

			Timeline messagesTimeline;
			vector<Text*> messageTextPtrs;

			Vector2f centerPos{0,0};
			
			float currentTime{0};
			float incrementTime{0};

			float timeStop{0};
			bool sideChanges{true};

			float radius{75};
			float minRadius{75};
			float radiusTimer{0};
			bool rotationDirection{true};			

			float fastSpin{0};

			bool hasDied{false};
			bool mustRestart{false};

			void update(float);
			inline void updateIncrement();
			inline void updateLevelEvents(float);
			inline void updateLevel(float);
			inline void updateColor(float);
			inline void updateRotation(float);
			inline void updateRadius(float);
			inline void updateDebugKeys();

			void drawDebugText();
			void drawBackground();

			void setLevelData(LevelData mLevelSettings);

			void playLevelMusic();
			void stopLevelMusic();

			void incrementDifficulty();
			void randomSideChange();
			void checkAndSaveScore();
			void goToMenu();
			void changeLevel(string mId);
			void addMessage(string mMessage, float mDuration);
			void clearMessages();

		public:
			MenuGame* mgPtr;

			HexagonGame(GameWindow& mGameWindow);
			~HexagonGame();

			void recreate();
			void startFromMenu(LevelData mLevelData);
			void newGame();
			void death();
			void drawOnTexture(Drawable&);
			void drawOnWindow(Drawable&);

			Game& getGame();
			Vector2f getCenterPos();
			float getRadius();
			Color getColorMain();
			Color getColorB();
			bool isKeyPressed(Keyboard::Key mKey);

			float getSpeedMultiplier();
			float getDelayMultiplier();
			float getRotationSpeed();
			int getSides();
			void setSpeedMultiplier(float mSpeedMultiplier);
			void setDelayMultiplier(float mDelayMultiplier);
			void setRotationSpeed(float mRotationSpeed);
			void setSides(int mSides);
	};
}
#endif /* HEXAGONGAME_H_ */