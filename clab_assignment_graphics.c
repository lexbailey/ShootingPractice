/*
 *  Copyright Daniel Bailey 2013 - 2014
 *  See clab_assignment_graphics.h for function documentation
 *  (University of York C Programming Labs assessment)
 */

#include "clab_assignment_graphics.h"

void drawFloor(){
	colourEnable(COLOUR_GRASS);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, gameData.grassTexture);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f,1.0f); glVertex3f(-5.0f, -1.5f, 0.0f);
		glTexCoord2f(1.0f,1.0f); glVertex3f(5.0f, -1.5f, 0.0f);
		glTexCoord2f(1.0f,0.5f); glVertex3f(5.0f, -3.0f, 0.0f);
		glTexCoord2f(0.0f,0.5f); glVertex3f(-5.0f, -3.0f, 0.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void keyboard(unsigned char key, int x, int y){
	//printf("Key: %c, x:%d, y:%d\n", key, x, y);
}

void keyboardSpecial(int key, int x, int y){
	//printf("Key: %d, x:%d, y:%d\n", key, x, y);
	onGLUTSpecialDown(key);
}

void keyboardSpecialUp(int key, int x, int y){
	onGLUTSpecialUp(key);
}

void mouse(int button, int state, int x, int y){
	gameData.leftClick = ((button == 0)&&(state==0));
	//printf("Button: %d, state: %d\n", button, state);
}

void motion(int x, int y){
	gameData.mousex = x;
	gameData.mousey = y;
}

void drawArrow (float pos){
	float flagHeight = 3.0f;
	float flagWidth = 14.0f;
	int stops = 90;
	float zVals[90];
	int i;
	for (i = 0; i< stops; i++){
		float mz = sin((i+(pos*stops)) IN_RADIANS);
		zVals[i] = mz;
	}

	float stepSize = flagWidth/stops;
	for (i = 0; i< stops-1; i++){
		float thisX = stepSize * i;
		glBegin(GL_QUADS);
			glVertex3f(thisX,0.0f+zVals[i],0.0f);
			glVertex3f(thisX,flagHeight+zVals[i],0.0f);
			glVertex3f(thisX+stepSize,flagHeight+zVals[i+1],0.0f);
			glVertex3f(thisX+stepSize,0.0f+zVals[i+1],0.0f);
		glEnd();
	}

	glBegin(GL_TRIANGLES);
		glVertex3f(0.0f, (zVals[0])+(flagHeight * 1.3f),0.0f);

		glVertex3f(-(flagWidth/3.0f),(flagHeight/2.0f)+zVals[0],0.0f);

		glVertex3f(0.0f, (zVals[0])-(flagHeight * 0.3f),0.0f);
	glEnd();
}

void drawWind(){
	if (gameData.windPower > 0.01f){ //if the level calls for wind
		float windScale = 0.5;

		glPushMatrix();
			colourEnable(COLOUR_WHITE);

			glTranslatef(WIND_INDICATOR_POS);
			glRotatef(gameData.windAngle, 0,0,1);
			glScalef(windScale,windScale,windScale);
			glPushMatrix();
				glScalef(0.1f,0.1f,0.1f);

				drawArrow((gameData.totTime/4.0f)*(gameData.windPower*5));
			glPopMatrix();

			glTranslatef(WIND_TEXT_OFFSET);
			if ((gameData.windAngle > 90)&&(gameData.windAngle < 270)){
				glRotatef(180, 0, 0, 1);
			}

			bitmapFontGLRenderTextCentre(gameData.MonospaceFont, "Wind", 0.3f);
		glPopMatrix();
	}
}

void initMenu(){

	gameData.miniStickMan.pos = vector3XYZ(MINI_STICKMAN_1_POS);
	gameData.miniStickMan.colour = COLOUR_STICKMAN1;
	gameData.miniStickMan.pullBack = 0;
	stickManSetPose(&(gameData.miniStickMan), ptStand);

	gameData.miniStickMan2.pos = vector3XYZ(MINI_STICKMAN_2_POS);
	gameData.miniStickMan2.colour = COLOUR_STICKMAN2;
	gameData.miniStickMan2.pullBack = 0;
	stickManSetPose(&(gameData.miniStickMan2), ptStand);

	gameData.myStickMan.pos = vector3XYZ(PLAYER_START_POS);
	gameData.myStickMan.colour = COLOUR_STICKMAN1;
	gameData.myStickMan.pullBack = 0;
	stickManSetPose(&(gameData.myStickMan), ptStand);

	gameData.SinglePlayerButton.fontMap = gameData.MonospaceFont;
	gameData.SinglePlayerButton.height = 0.5f;
	gameData.SinglePlayerButton.width = 4.0f;
	gameData.SinglePlayerButton.x = -2.0f;
	gameData.SinglePlayerButton.y = +0.0f;
	gameData.SinglePlayerButton.text = "Single Player Mode";
	gameData.SinglePlayerButton.colour = COLOUR_ONEPLAYER_BUTTON;

	gameData.TwoPlayerButton.fontMap = gameData.MonospaceFont;
	gameData.TwoPlayerButton.height = 0.5f;
	gameData.TwoPlayerButton.width = 4.0f;
	gameData.TwoPlayerButton.x = -2.0f;
	gameData.TwoPlayerButton.y = -1.0f;
	gameData.TwoPlayerButton.text = "Two Player Mode";
	gameData.TwoPlayerButton.colour = COLOUR_TWOPLAYER_BUTTON;


	gameData.CreditsButton.fontMap = gameData.MonospaceFont;
	gameData.CreditsButton.height = 0.5f;
	gameData.CreditsButton.width = 2.3f;
	gameData.CreditsButton.x = -5.0f;
	gameData.CreditsButton.y = -3.0f;
	gameData.CreditsButton.text = "Credits";
	gameData.CreditsButton.colour = COLOUR_ONEPLAYER_BUTTON;

	gameData.FullscreenButton.fontMap = gameData.MonospaceFont;
	gameData.FullscreenButton.height = 0.5f;
	gameData.FullscreenButton.width = 2.3f;
	gameData.FullscreenButton.x = -1.15f;
	gameData.FullscreenButton.y = -3.0f;
	gameData.FullscreenButton.text = "Fullscreen";
	gameData.FullscreenButton.colour = COLOUR_ONEPLAYER_BUTTON;

	gameData.InstructionsButton.fontMap = gameData.MonospaceFont;
	gameData.InstructionsButton.height = 0.5f;
	gameData.InstructionsButton.width = 2.3f;
	gameData.InstructionsButton.x = +2.7f;
	gameData.InstructionsButton.y = -3.0f;
	gameData.InstructionsButton.text = "How to play";
	gameData.InstructionsButton.colour = COLOUR_ONEPLAYER_BUTTON;


	gameData.totTime = 0.0f;
}

void restartMenu(){
	gameData.totTime = 8.0f;
}

float motionAnimation(float animationTime, float animationDistance, float curTime){
	return (curTime < animationTime)?
			animationDistance - ((curTime / animationTime) * animationDistance)
			:
			0.0f;
}

void drawGameMenu(float time_delta){

	gameData.totTime += time_delta;
	float textAdjustment = 0.0f;
	float textAnimationTime = 2.0f;
	textAdjustment = motionAnimation(textAnimationTime, 30.0f, gameData.totTime);

	float floorAdjustment = 0.0f;
	float floorAnimationTime = 4.0f;
	floorAdjustment = motionAnimation(floorAnimationTime, 7.5f, gameData.totTime);

	float stickAdjustment = 0.0f;
	stickAdjustment = motionAnimation(8.0f, 10.0f, gameData.totTime);

	//get mouse pos
	vector3 mouse = glWindowGetOGLPos(gameData.mousex, gameData.mousey);

	//if the main menu buttons have appeared (the animation is done) then deal with them...
	if (gameData.totTime > textAnimationTime){
		bool singlePlayHovered = buttonIsHovered(&(gameData.SinglePlayerButton), mouse);
		bool twoPlayHovered = buttonIsHovered(&(gameData.TwoPlayerButton), mouse);

		//manage hover
		gameData.SinglePlayerButton.colour =
				singlePlayHovered? COLOUR_WHITE : COLOUR_ONEPLAYER_BUTTON;
		gameData.TwoPlayerButton.colour =
				twoPlayHovered? COLOUR_WHITE : COLOUR_TWOPLAYER_BUTTON;

		//As an extra little treat, mini stickmen appear on hovered buttons...
		if (singlePlayHovered){
			glPushMatrix();
				glTranslatef(gameData.SinglePlayerButton.x + 0.2f, gameData.SinglePlayerButton.y+0.4, 0.0f);
				glScalef(0.2f,0.2f,0.2f);
				stickManDraw(&(gameData.miniStickMan));
			glPopMatrix();
		}

		if (twoPlayHovered){
			glPushMatrix();
				glTranslatef(gameData.TwoPlayerButton.x + 0.2f, gameData.TwoPlayerButton.y+0.4, 0.0f);
				glScalef(0.2f,0.2f,0.2f);
				stickManDraw(&(gameData.miniStickMan));
				stickManDraw(&(gameData.miniStickMan2));
			glPopMatrix();
		}

		//if one is clicked, do the action
		if (gameData.leftClick){
			if (singlePlayHovered){
				setGameState(gs_OnePlay);
			}
			else{
				if (twoPlayHovered){
					setGameState(gs_TwoPlay);
				}
			}
		}
	}

	//if the floor has appeared then deal with the buttons on the floor
	if (gameData.totTime > floorAnimationTime){

		//manage hover
		gameData.CreditsButton.colour =
				buttonIsHovered(&(gameData.CreditsButton), mouse)? COLOUR_WHITE : COLOUR_ONEPLAYER_BUTTON;
		gameData.InstructionsButton.colour =
				buttonIsHovered(&(gameData.InstructionsButton), mouse)? COLOUR_WHITE : COLOUR_ONEPLAYER_BUTTON;
		gameData.FullscreenButton.colour =
				buttonIsHovered(&(gameData.FullscreenButton), mouse)? COLOUR_WHITE : COLOUR_ONEPLAYER_BUTTON;

		//if the user clicked
		if (gameData.leftClick){
			//see if a button is hovered, if so perform the correct action for that button
			if (buttonIsHovered(&(gameData.CreditsButton), mouse)){
				setGameState(gs_Credits);
			}
			if (buttonIsHovered(&(gameData.InstructionsButton), mouse)){
				setGameState(gs_Instructions);
			}
			if (buttonIsHovered(&(gameData.FullscreenButton), mouse)){
				glutFullScreenToggle();
			}
		}
	}

	//Drawing of the title and the buttons
	glPushMatrix();
		//Move by animation adjustment amount
		glTranslatef(textAdjustment, 0.0f, 0.0f);
		//Draw buttons
		buttonDraw(&(gameData.SinglePlayerButton));
		buttonDraw(&(gameData.TwoPlayerButton));
		//Draw the title
		glTranslatef(TITLE_POS);
		bitmapFontGLRenderText(gameData.SketchyFont, "Shooting", 1.0f);
		glTranslatef(TITLE_LINE2_OFFSET);
		bitmapFontGLRenderText(gameData.SketchyFont, "Practice", 1.0f);
	glPopMatrix();

	//Draw floor and other buttons
	glPushMatrix();
		//Another animation adjustment
		glTranslatef(0.0f, -floorAdjustment, 0.0f);
		//floor
		drawFloor();
		//buttons
		buttonDraw(&(gameData.InstructionsButton));
		buttonDraw(&(gameData.FullscreenButton));
		buttonDraw(&(gameData.CreditsButton));
	glPopMatrix();

	//And finally, the stickman
	glPushMatrix();
		glTranslatef(-stickAdjustment,-1.50f,0.0f);
		stickManDraw(&(gameData.myStickMan));
	glPopMatrix();
}

void initGame(){
	gameData.myStickMan.pos = vector3XYZ(PLAYER_START_POS);
	gameData.myStickMan.colour = COLOUR_STICKMAN1;
	gameData.myStickMan.pullBack = 0;
	stickManSetPose(&(gameData.myStickMan), ptStand);

	gameData.miniStickMan.pos = vector3XYZ(MINI_STICKMAN_1_POS);
	gameData.miniStickMan.pose = ptStand;
	gameData.miniStickMan.colour = COLOUR_STICKMAN1;
	gameData.miniStickMan.pullBack = 0;
	stickManSetPose(&(gameData.miniStickMan), ptStand);

	gameData.ExitButton.fontMap = gameData.MonospaceFont;
	gameData.ExitButton.height = 0.5f;
	gameData.ExitButton.width = 1.0f;
	gameData.ExitButton.x = -5.0f;
	gameData.ExitButton.y = -3.0f;
	gameData.ExitButton.text = "Exit";
	gameData.ExitButton.colour = COLOUR_EXIT_BUTTON;

	// a constraint to stop the arrow falling below the ground
	gameData.floorConstraint.type = ct_MinTranslation;
	gameData.floorConstraint.axis = y_axis;
	gameData.floorConstraint.value = -0.02f;
}

void initOnePlay(){

	initGame();
	gameData.level = 1;
	gameData.lives = 3;
	gameData.numPlayers =1;
	gameData.player = 1;
	restartOnePlay();
}

void restartGame(){

	gameData.loadLevel = gameData.level;

	if (gameData.numPlayers == 2){
		//if we are in two player mode handle the right level and player
		if (gameData.player == 1){
			gameData.myStickMan.colour = COLOUR_STICKMAN1;
			gameData.miniStickMan.colour = COLOUR_STICKMAN1;
			gameData.loadLevel = gameData.level;
		}
		else{
			gameData.myStickMan.colour = COLOUR_STICKMAN2;
			gameData.miniStickMan.colour = COLOUR_STICKMAN2;
			gameData.loadLevel = gameData.level2;
		}
	}

	//if there is an old level in memory, free it
	if (gameData.levelData.obstructions){
		levelFree(&(gameData.levelData));
	}
	gameData.levelData = levelGet(gameData.loadLevel);

	//if the projectile is still there, free it
	if (gameData.projectileP){
		physObjFree(gameData.projectileP);
		gameData.projectileP = NULL;
	}

	//if there is a physics world still in memory, free it
	if (gameData.physWorld.physObjects){
		physWorldFree(&(gameData.physWorld));
	}

	//start again with a new world, it must have enough space for all obstructions and the arrow
	physWorldInitialise(&(gameData.physWorld), vector3XYZ(GRAVITY), gameData.levelData.numObstructions + 1);
	gameData.physWorld.windSpeed = gameData.levelData.wind;

	//Initialise the projectile
	physObjInitialise(&(gameData.projectile), gameData.myStickMan.top, 0,1);

	//Set up the arrow
	gameData.projectile.mass = 0.010;//kilos = 10 grams
	gameData.projectile.collisionBounds = pcb_Circle;
	gameData.projectile.collisionRadius = PROJECTILE_RADIUS;
	gameData.projectile.relativeCOR = 0.9f; //a very bouncy arrow indeed

	//Make sure it won't fall under the ground
	physObjAddConstraint(&(gameData.projectile), gameData.floorConstraint);

	gameData.projectileP = physWorldAddObject(&(gameData.physWorld), gameData.projectile);

	//Add all of the obstructions to the physics world
	int i;
	int obst = gameData.levelData.numObstructions;
	//Loop through all obstructions
	for (i = 0; (i<=(obst-1)); i++){
		//if it is a bouncy one
		if (gameData.levelData.obstructions[i].obsType==ot_Bounce){
			//add it to the physics simulation world
			physics_object_t bouncer;
			physObjInitialise(&bouncer, gameData.levelData.obstructions[i].pos, 0, 0);
			//it is a circle
			bouncer.collisionBounds = pcb_Circle;
			bouncer.collisionRadius = gameData.levelData.obstructions[i].radius;
			//it is bouncy
			bouncer.relativeCOR = 0.99f;//nearly 1
			//it stays still
			bouncer.isStatic = true;
			physWorldAddObject(&(gameData.physWorld), bouncer);
		}
		//if it is a 'death zone' then don't add it, those are checked manually.
	}

	//Get the wind arrow ready
	gameData.windAngle = vector3Rotation(gameData.levelData.wind, z_axis);
	gameData.windPower = vector3Length(gameData.levelData.wind);

	gameData.totTime = 0.0f;
	gameData.hasWon = false;
	gameData.hasDied = false;
	gameData.hasFired = false;
	gameData.isGameOver = false;
}

void restartOnePlay(){
	restartGame();
}

void drawStats(const char *levelText){
	//prepare the stats
	char *lifeText;
	lifeText = malloc(10); //up to 9 chars plus a null
	//Prepared text depends on who's playing
	if ((gameData.numPlayers == 1) || (gameData.player ==1)){
		if (gameData.lives == 1)
			snprintf(lifeText, 10, "1 Life");
		else
			snprintf(lifeText, 10, "%d Lives", gameData.lives);
	}
	else{
		if (gameData.lives2 == 1)
			snprintf(lifeText, 10, "1 Life");
		else
			snprintf(lifeText, 10, "%d Lives", gameData.lives2);
	}

	//handle the two player mode stats (player ID and time)
	if (gameData.numPlayers > 1){
		char *playerText;
		playerText = malloc(9); //up to 2 chars plus a null
		snprintf(playerText, 9, "Player %d", gameData.player);

		//For two player mode, display the current player number
		glPushMatrix();
			glTranslatef(PLAYER_ID_LOCATION);
			bitmapFontGLRenderTextCentre(gameData.MonospaceFont, playerText, 0.3f);
		glPopMatrix();

		//if we are in two player mode, display the timer
		char *timeLeftText = malloc(5);
		snprintf(timeLeftText, 5, "%.1f", gameData.timeLeft);
		glPushMatrix();
			glTranslatef(PLAYER_TIMER_LOCATION);
			bitmapFontGLRenderTextCentre(gameData.MonospaceFont, timeLeftText, 0.5f);
		glPopMatrix();

		free(playerText);
		free(timeLeftText);
	}

	//Show the level number
	glPushMatrix();
		glTranslatef(LEVEL_ID_LOCATION);
		bitmapFontGLRenderTextCentre(gameData.MonospaceFont, levelText, 0.3f);
	glPopMatrix();

	//Show the life indicator
	glPushMatrix();
		glTranslatef(LIFE_INDICATOR_LOCATION);
		bitmapFontGLRenderTextCentre(gameData.MonospaceFont, lifeText, 0.3f);

		glTranslatef(LIFE_STICKS_OFFSET);
		glScalef(0.2f,0.2f,0.2f);
		int i;
		int lives = (gameData.player==1)?gameData.lives:gameData.lives2;
		for (i=1; i<= lives; i++){
			stickManDraw(&(gameData.miniStickMan));
			glTranslatef(LIFE_STICKS_SEPERATION);
		}

	glPopMatrix();

	free(lifeText);
}

void drawHeaderText(const char* text){
	glPushMatrix();
		//move to the header text position
		glTranslatef(HEADER_TEXT_POS);
		//render the text
		bitmapFontGLRenderTextCentre(gameData.SketchyFont, text, 1.0f);
	glPopMatrix();
}

void handleFiring(){
	//Mouse button clicked, player is about to fire
	if (glWindowData.mousebuttons[0]){
		//when the player clicks, the stickman should go into fire mode
		gameData.myStickMan.pose = ptFire;
		gameData.hasFired = false;
	}

	//Mouse button released, Player has released the bow and arrow
	if (((!glWindowData.mousebuttons[0]) && (gameData.myStickMan.pose == ptFire)) && (!gameData.hasFired)){
		//Do physics!
		//Put the projectile back at the start
		physObjReset(gameData.projectileP, gameData.myStickMan.top);

		//calculate its angle and power
		float angle = gameData.myStickMan.aimAngle IN_RADIANS;
		float power = (gameData.myStickMan.pullBack) * BOW_POWER;

		//from that, calculate its speed in x and in y
		float xVel = cos(angle)*power;
		float yVel = sin(angle)*power;

		//create a force to handle it
		force_t launch;
		//It is an explosive force (an impulse)
		launch.type = ft_Explosive;
		launch.impulseTime = 0.05f; //bow fires in 50ms
		launch.forceVector.x = xVel;
		launch.forceVector.y = yVel;
		launch.forceVector.z = 0;

		//add the force!
		physObjAddForce(gameData.projectileP, launch);
		//note that we do not need to keep a pointer to it, it is explosive and so it isn't added to the array of forces

		//we have now fired
		gameData.hasFired = true;
		//go back to standing
		gameData.myStickMan.pose = ptStand;
	}
}

void drawProjectile() {
	glPushMatrix();
		//move to where the projectile is to be drawn
		drawFuncApplyTranslation(gameData.projectileP->currentPos);
		//Calculate the angle of the  projectile simply using it's change in position (a good approximation for now)
		float changeX = gameData.projectileP->currentPos.x - gameData.projectileP->prevPos.x;
		float changeY = gameData.projectileP->currentPos.y - gameData.projectileP->prevPos.y;
		float angle = atan(changeY / changeX)IN_DEGREES;
		//Rotate by that angle
		glRotatef(angle, 0, 0, 1);
		//Draw the body of the arrow
		drawFuncLine(vector3GetNull(), vector3XYZ(ARROW_END_POS));
		//Draw the head of the arrow
		drawFuncCircle(vector3GetNull(), PROJECTILE_RADIUS, 30);
	glPopMatrix();

}

void drawLevel() {
	//Draw the target first
	colourEnable(COLOUR_TARGET);
	drawFuncDisc(gameData.levelData.target, gameData.levelData.targetSize, 30);

	int i;
	//number of obstructions must be cast to int to allow negative.
	int obst = gameData.levelData.numObstructions;
	//loop through all obstructions
	for (i = 0; i <= (obst - 1); i++) {
		//pick the correct colour for drawing this obstruction
		switch (gameData.levelData.obstructions[i].obsType) {
		case ot_Bounce:
			colourEnable(COLOUR_OBS_BOUNCE);
			break;
		case ot_Die:
			colourEnable(COLOUR_OBS_DIE);
			break;
		}
		//Draw the obstruction
		drawFuncDisc(gameData.levelData.obstructions[i].pos,
				gameData.levelData.obstructions[i].radius, 30);
	}
}

void aimBowAtCursor() {
	//Get the mouse pos
	gameData.mousePos = glWindowGetOGLPos(gameData.mousex, gameData.mousey);
	vector3 flatMousePos = gameData.mousePos;
	//ensure that there is no z component
	flatMousePos.z = 0;
	//Calculate how far away the cursor is from the stickman
	float distance = vector3DistanceBetween(flatMousePos,	gameData.myStickMan.top);

	//see if the cursor is far-enough away to go into fire mode
	if (distance > (ARMDROP*2)){
		//Calculate the fire angle
		float B1 = (gameData.mousePos.x - gameData.myStickMan.top.x);
		float P1 = (gameData.mousePos.y - gameData.myStickMan.top.y);
		float gradient = P1 / B1;
		float theta1 = (atan(gradient)IN_DEGREES);
		float hyp1 = sqrt((B1 * B1) + (P1 * P1));
		float P2 = ARMDROP;
		float theta2 = (asin(P2 / hyp1)IN_DEGREES);
		float thetaTot = theta1 + theta2;
		gameData.myStickMan.aimAngle = (thetaTot);
		gameData.myStickMan.pullBack = distance / 10;
		stickManSetPose(&(gameData.myStickMan), gameData.myStickMan.pose);
	}
	else{
		//if too close, don't fire
		stickManSetPose(&(gameData.myStickMan), ptStand);
	}


}

void handleFloorBounce() {
	if ((gameData.projectileP->currentPos.y < PROJECTILE_RADIUS)
			&& (gameData.projectileP->velocity.y < 0)) {
		float cor = 0.3f; //coefficient of restitution.
		//calculate bounce, taken from http://www.3dkingdoms.com/weekly/weekly.php?a=2
		gameData.projectileP->velocity = vector3ScalarProduct(
				vector3Reflection(gameData.projectileP->velocity, vector3XYZ(FLOOR_COLLISION_NORMAL)), cor);
	}
}

void handleTargetHit(float time_delta) {
	//check to see if they have hit the target
	if (collisionMovingCircleStaticCircle(*(gameData.projectileP),
			PROJECTILE_RADIUS, gameData.levelData.target,
			gameData.levelData.targetSize, time_delta)) {

		//You WIN!
		gameData.hasWon = true;
		gameData.hasFired = false;
		gameData.endTime = gameData.totTime;
		if (gameData.level < NUM_LEVELS) {
			if (gameData.player == 1){ //if it's player 1
				gameData.level++;
			}
			else{//if its player 2
				gameData.level2++;
			}

		} else {
			gameData.isGameOver = true;
		}
	}
}

void loseLife() {
	//loose a life
	gameData.hasDied = true;
	gameData.hasFired = false;
	gameData.endTime = gameData.totTime;
	int livesLeft;
	if (gameData.player == 1) {
		//if it's player 1
		livesLeft = --gameData.lives;
	} else {
		//if its player 2
		livesLeft = --gameData.lives2;
	}
	//if dead, game over
	if (livesLeft < 0) {
		gameData.lives = 0; //just to avoid seeing "lives: -1"
		gameData.lives2 = 0;
		gameData.hasDied = false;
		gameData.isGameOver = true;
		gameData.loser = gameData.player;
	}
}

void handleObstaclesHit(float time_delta) {
	//See if an obstacle is hit
	int i;
	int obst = gameData.levelData.numObstructions;
	for (i = 0;	(i <= (obst - 1))
				&& ((!gameData.hasWon) && (!gameData.hasDied)
				&& (!gameData.isGameOver));
				i++) {

		if (	//if the obstruction is a death zone and you have hit it...
		(gameData.levelData.obstructions[i].obsType == ot_Die)
				&& (collisionMovingCircleStaticCircle(*(gameData.projectileP),
						PROJECTILE_RADIUS,
						gameData.levelData.obstructions[i].pos,
						gameData.levelData.obstructions[i].radius, time_delta))) {
			//loose a life
			loseLife();
		}
	}
}

void handleWalk(float time_delta) {
	//If the stickman is standing then allow the player to move left and right
	if (gameData.myStickMan.pose == ptStand) {
		if (keyData.arrowKeysPressed[KEY_A_LEFT]) {
			gameData.myStickMan.pos.x -= time_delta * WALK_SPEED;
		}

		if (keyData.arrowKeysPressed[KEY_A_RIGHT]) {
			gameData.myStickMan.pos.x += time_delta * WALK_SPEED;
		}

		//Keep him within the limits
		if (gameData.myStickMan.pos.x < -4.5f)
			gameData.myStickMan.pos.x = -4.5f;
		if (gameData.myStickMan.pos.x > -1.0f)
			gameData.myStickMan.pos.x = -1.0f;
	}
}

void manageGameButtons(float goTime) {
	//get the mouse location
	gameData.mousePos = glWindowGetOGLPos(gameData.mousex, gameData.mousey);
	//see if the mouse is over the button
	if (buttonIsHovered(&gameData.ExitButton, gameData.mousePos) && (gameData.totTime > goTime)) {
		//change colour to indicate hover
		gameData.ExitButton.colour = COLOUR_WHITE;
		//se if the user clicked
		if (gameData.leftClick) {
			//click action (exit game)
			gameData.loser = gameData.player; //the player that pressed exit is declared the loser (for 2 player mode)
			gameData.endTime = gameData.totTime;
			gameData.isGameOver = true;
		}
	} else {
		//return to default colour if not hovered
		gameData.ExitButton.colour = COLOUR_EXIT_BUTTON;
	}
	//draw the button
	buttonDraw(&(gameData.ExitButton));

}

void drawGame(float time_delta){
	//the big game draw function
	//move along by the correct amount of time
	gameData.totTime += time_delta;
	float animTime = 2.0f;
	float goTime = 4.0f;
	float outTime = 2.0f;

	//prepare the level text
	char *levelText;
	levelText = malloc(10); //up to 9 chars plus a null
	snprintf(levelText, 10, "Level %d", gameData.loadLevel);

	//see if the intro animation should still be playing
	if (gameData.totTime <= animTime){
		//Display the level text during the intro
		drawHeaderText(levelText);
		//The intro animation is a scale and rotate
		float rotation = 90 * (1-(gameData.totTime/animTime));
		float scale = (gameData.totTime/animTime);
		glScalef(scale, scale, scale); //scale evenly
		glRotatef(rotation, 1, 1, 0);  //rotate on x and y but not z
	}
	else{
		//if the intro has finished and the game is still playing...
		if ((!gameData.hasWon && !gameData.hasDied) && !gameData.isGameOver){
			//if the animation only finished recently...
			if (gameData.totTime <= goTime){
				//Say go!
				drawHeaderText("Go!");
			}

			if (gameData.numPlayers == 2){
				//if we are in two player mode, decmenet the time
				gameData.timeLeft -= time_delta;
				if (gameData.timeLeft <= 0.0f){
					//time up us two lives lost
					loseLife();
					loseLife();
				}
			}
		}
	}

	//see if we need to exit the game
	if (gameData.hasWon || gameData.hasDied || gameData.isGameOver){
		float rotation = 90 * (((gameData.totTime-gameData.endTime)/outTime));
		float scale = 1-((gameData.totTime-gameData.endTime)/outTime);

		//Display the correct end text
		if (gameData.hasWon){drawHeaderText("You win!");}
		else{
			if (gameData.isGameOver){
				if (gameData.numPlayers == 1){

					drawHeaderText("Game Over!");
				}
				else{
					char *lost = malloc(8);
					snprintf(lost, 8, "P%d Lost", gameData.loser);
					drawHeaderText(lost);
					free(lost);
				}
			}
			else{
				if (gameData.hasDied){drawHeaderText("You died!");}
			}
		}
		//apply the appropriate transformation for leaving
		glScalef(scale, scale, scale);
		glRotatef(rotation, 1, 1, 0);
	}

	drawStats(levelText);	//render the level number and lives left
	free(levelText);	//free once it is no longer needed
	drawWind();		//render the wind indicator ('windicator'?)

	if ((gameData.endTime+outTime) < gameData.totTime){

		//once done, if the game is not over, reset for next level
		if ((gameData.hasWon&& !gameData.isGameOver) || gameData.hasDied){

			//if we are in two player mode and somebody died, switch players
			if ((gameData.numPlayers == 2) && (gameData.hasDied)) {
				if (gameData.player == 1) {
					gameData.player = 2;
				} else {
					gameData.player = 1;
				}
			}

			//Then restart
			reSetGameState(gameData.gameState); //restart this state (either 1 or two player mode)
		}
		//if the game is over, go back to the main menu
		if (gameData.isGameOver){setGameState(gs_Menu);}
	}

	if ((gameData.totTime >= animTime) &&(!gameData.hasWon)){
		//If the stickman is standing then allow the player to move left and right
		handleWalk(time_delta);
		//Handle firing an arrow
		handleFiring();
	}

	drawFloor();

	manageGameButtons(goTime);

	glPushMatrix();
		glTranslatef(GROUND_LEVEL);

		drawLevel();
		aimBowAtCursor();
		stickManDraw(&(gameData.myStickMan));
		if (gameData.hasFired){

			handleFloorBounce();

			//if the game is still running
			if ((!gameData.hasWon)&&(!gameData.hasDied)&&(!gameData.isGameOver)){
				//check to see if they have hit the target
				handleTargetHit(time_delta);

				//or an obstacle
				handleObstaclesHit(time_delta);
			}
			physWorldStep(&(gameData.physWorld), time_delta);
			drawProjectile();
		}

	glPopMatrix();
}

void drawOnePlay(float time_delta){
	drawGame(time_delta);
}

void initTwoPlay(){
	initGame();
	gameData.level = 1;
	gameData.level2 = 1;
	gameData.lives = 3;
	gameData.lives2 = 3;
	gameData.numPlayers =2;
	gameData.player = 1;
	restartTwoPlay();
}

void restartTwoPlay(){
	gameData.timeLeft = 15.0f;
	restartGame();
}

void drawTwoPlay(float time_delta){
	drawGame(time_delta);
}

void initInstructions(){
	gameData.ExitButton.fontMap = gameData.MonospaceFont;
	gameData.ExitButton.height = 0.5f;
	gameData.ExitButton.width = 3.0f;
	gameData.ExitButton.x = -1.5f;
	gameData.ExitButton.y = -3.0f;
	gameData.ExitButton.text = "Back";

	gameData.NextButton.fontMap = gameData.MonospaceFont;
	gameData.NextButton.height = 0.5f;
	gameData.NextButton.width = 3.0f;
	gameData.NextButton.x = +2.0f;
	gameData.NextButton.y = -3.0f;
	gameData.NextButton.text = "Next";


	gameData.PrevButton.fontMap = gameData.MonospaceFont;
	gameData.PrevButton.height = 0.5f;
	gameData.PrevButton.width = 3.0f;
	gameData.PrevButton.x = -5.0f;
	gameData.PrevButton.y = -3.0f;
	gameData.PrevButton.text = "Previous";
	restartInstructions();
}

void restartInstructions(){
	gameData.manPage = 1;
}

void drawInstructions(float time_delta){
	gameData.mousePos = glWindowGetOGLPos(gameData.mousex, gameData.mousey);

	bool nextHovered = buttonIsHovered(&(gameData.NextButton), gameData.mousePos);
	bool prevHovered = buttonIsHovered(&(gameData.PrevButton), gameData.mousePos);
	bool exitHovered = buttonIsHovered(&(gameData.ExitButton), gameData.mousePos);

	//manage hover
	gameData.NextButton.colour =
			nextHovered? COLOUR_WHITE : COLOUR_ONEPLAYER_BUTTON;
	gameData.PrevButton.colour =
			prevHovered? COLOUR_WHITE : COLOUR_ONEPLAYER_BUTTON;

	gameData.ExitButton.colour =
				exitHovered? COLOUR_WHITE : COLOUR_ONEPLAYER_BUTTON;

	//if one is clicked, do the action
	if (gameData.leftClick){
		if (nextHovered){
			//ne
			if (gameData.manPage <NUM_MAN_PAGES){
				gameData.manPage++;
			}
		}
		else{
			if (prevHovered){
				//prev
				if (gameData.manPage >1){
					gameData.manPage--;
				}
			}
			else{
				if(exitHovered){
					reSetGameState(gs_Menu);
				}
			}
		}
	}

	buttonDraw(&(gameData.ExitButton));
	//only show next or prev if they do something
	if (gameData.manPage <NUM_MAN_PAGES){buttonDraw(&(gameData.NextButton));}
	if (gameData.manPage >1){buttonDraw(&(gameData.PrevButton));}

	glTranslatef(TITLE_POS);
	bitmapFontGLRenderText(gameData.SketchyFont, "How to", 1.0f);
	glTranslatef(TITLE_LINE2_OFFSET);
	bitmapFontGLRenderText(gameData.SketchyFont, "play...", 1.0f);

	glPushMatrix();
	glTranslatef(TEXT_LINES_START);
	//Render the correct page for the how-to-play
	switch (gameData.manPage){
		case 1:
			bitmapFontGLRenderText(gameData.MonospaceFont, "The aim of the game is to hit the yellow target", 0.2f);
			glTranslatef(TEXT_SINGLE_LINE_SPACE);
			bitmapFontGLRenderText(gameData.MonospaceFont, "with your bow and arrow. You must reach the", 0.2f);
			glTranslatef(TEXT_SINGLE_LINE_SPACE);
			bitmapFontGLRenderText(gameData.MonospaceFont, "target on each level before you can move to the", 0.2f);
			glTranslatef(TEXT_SINGLE_LINE_SPACE);
			bitmapFontGLRenderText(gameData.MonospaceFont, "next level.", 0.2f);

			glTranslatef(TEXT_DOUBLE_LINE_SPACE);
			bitmapFontGLRenderText(gameData.MonospaceFont, "Hit these -->", 0.2f);
			colourEnable(COLOUR_TARGET);
			glTranslatef(3.0f, 0.0f, 0.0f);
			drawFuncDisc(vector3GetNull(), 0.3f, 30);
		break;

		case 2:
			bitmapFontGLRenderText(gameData.MonospaceFont, "To aim the bow you can click and hold in the ", 0.2f);
			glTranslatef(TEXT_SINGLE_LINE_SPACE);
			bitmapFontGLRenderText(gameData.MonospaceFont, "main game scene. As you move the mouse, the ", 0.2f);
			glTranslatef(TEXT_SINGLE_LINE_SPACE);
			bitmapFontGLRenderText(gameData.MonospaceFont, "stickman will point his bow at the cursor.", 0.2f);

			glTranslatef(TEXT_DOUBLE_LINE_SPACE);
			bitmapFontGLRenderText(gameData.MonospaceFont, "The further the cursor is from the bow, the", 0.2f);
			glTranslatef(TEXT_SINGLE_LINE_SPACE);
			bitmapFontGLRenderText(gameData.MonospaceFont, "more the stickman will pull the bow back.", 0.2f);

			glTranslatef(TEXT_DOUBLE_LINE_SPACE);
			bitmapFontGLRenderText(gameData.MonospaceFont, "The stickman will fire the bow when you release", 0.2f);
			glTranslatef(TEXT_SINGLE_LINE_SPACE);
			bitmapFontGLRenderText(gameData.MonospaceFont, "the mouse button.", 0.2f);
		break;

		case 3:
			bitmapFontGLRenderText(gameData.MonospaceFont, "If you need to do so, you can stop an arrow", 0.2f);
			glTranslatef(TEXT_SINGLE_LINE_SPACE);
			bitmapFontGLRenderText(gameData.MonospaceFont, "early by clicking and holding again. This can", 0.2f);
			glTranslatef(TEXT_SINGLE_LINE_SPACE);
			bitmapFontGLRenderText(gameData.MonospaceFont, "be useful if you think that the arrow will miss", 0.2f);
			glTranslatef(TEXT_SINGLE_LINE_SPACE);
			bitmapFontGLRenderText(gameData.MonospaceFont, "or might hit an instant death obstacle.", 0.2f);

			glTranslatef(TEXT_DOUBLE_LINE_SPACE);
			bitmapFontGLRenderText(gameData.MonospaceFont, "This is also helpful when trying to find a", 0.2f);
			glTranslatef(TEXT_SINGLE_LINE_SPACE);
			bitmapFontGLRenderText(gameData.MonospaceFont, "precise angle at which to fire.", 0.2f);
		break;

		case 4:
			bitmapFontGLRenderText(gameData.MonospaceFont, "You can move the stickman left or right to get", 0.2f);
			glTranslatef(TEXT_SINGLE_LINE_SPACE);
			bitmapFontGLRenderText(gameData.MonospaceFont, "into a better position for reaching the target", 0.2f);
			glTranslatef(TEXT_SINGLE_LINE_SPACE);
			bitmapFontGLRenderText(gameData.MonospaceFont, "by using the left and right arrow keys on your", 0.2f);
			glTranslatef(TEXT_SINGLE_LINE_SPACE);
			bitmapFontGLRenderText(gameData.MonospaceFont, "keyboard.", 0.2f);
		break;

		case 5:
			bitmapFontGLRenderText(gameData.MonospaceFont, "Obstructions will appear in most levels to make", 0.2f);
			glTranslatef(TEXT_SINGLE_LINE_SPACE);
			bitmapFontGLRenderText(gameData.MonospaceFont, "reaching the target more difficult.", 0.2f);
			glTranslatef(TEXT_SINGLE_LINE_SPACE);
			bitmapFontGLRenderText(gameData.MonospaceFont, "Red obstructions must be avoided. If you hit", 0.2f);
			glTranslatef(TEXT_SINGLE_LINE_SPACE);
			bitmapFontGLRenderText(gameData.MonospaceFont, "one you will lose a life. Lose all your lives", 0.2f);
			glTranslatef(TEXT_SINGLE_LINE_SPACE);
			bitmapFontGLRenderText(gameData.MonospaceFont, "and it's game over.", 0.2f);
			glTranslatef(TEXT_SINGLE_LINE_SPACE);
			bitmapFontGLRenderText(gameData.MonospaceFont, "Green obstructions are not deadly. Arrows will", 0.2f);
			glTranslatef(TEXT_SINGLE_LINE_SPACE);
			bitmapFontGLRenderText(gameData.MonospaceFont, "rebound when they hit green obstructions.", 0.2f);


			glTranslatef(TEXT_DOUBLE_LINE_SPACE);
			bitmapFontGLRenderText(gameData.MonospaceFont, "Deadly -->", 0.2f);
			colourEnable(COLOUR_OBS_DIE);
			glTranslatef(3.0f, 0.0f, 0.0f);
			drawFuncDisc(vector3GetNull(), 0.3f, 30);

			glTranslatef(1.0f, 0.0f, 0.0f);
			bitmapFontGLRenderText(gameData.MonospaceFont, "Bouncy -->", 0.2f);
			colourEnable(COLOUR_OBS_BOUNCE);
			glTranslatef(3.0f, 0.0f, 0.0f);
			drawFuncDisc(vector3GetNull(), 0.3f, 30);
		break;

		case 6:
			bitmapFontGLRenderText(gameData.MonospaceFont, "When using two player mode, each player is ", 0.2f);
			glTranslatef(TEXT_SINGLE_LINE_SPACE);
			bitmapFontGLRenderText(gameData.MonospaceFont, "timed. They have 15 seconds per level.", 0.2f);
			glTranslatef(TEXT_SINGLE_LINE_SPACE);
			bitmapFontGLRenderText(gameData.MonospaceFont, "Run out of time and you forfeit two lives.", 0.2f);
			glTranslatef(TEXT_SINGLE_LINE_SPACE);
			bitmapFontGLRenderText(gameData.MonospaceFont, "Any time a player loses a life, the next player", 0.2f);
			glTranslatef(TEXT_SINGLE_LINE_SPACE);
			bitmapFontGLRenderText(gameData.MonospaceFont, "is then allowed to play.", 0.2f);

			glTranslatef(TEXT_DOUBLE_LINE_SPACE);
			bitmapFontGLRenderText(gameData.MonospaceFont, "The winner is the one that reaches the end", 0.2f);
			glTranslatef(TEXT_SINGLE_LINE_SPACE);
			bitmapFontGLRenderText(gameData.MonospaceFont, "first or is last to lose all of their lives.", 0.2f);
		break;
	}
	glPopMatrix();

}

void initCredits(){
	//the credits only need a back button
	gameData.ExitButton.fontMap = gameData.MonospaceFont;
	gameData.ExitButton.height = 0.5f;
	gameData.ExitButton.width = 3.0f;
	gameData.ExitButton.x = -1.5f;
	gameData.ExitButton.y = -3.0f;
	gameData.ExitButton.text = "Got it!";
}

void restartCredits(){

}

void drawCredits(float time_delta){
	//the credits window is simple.
	//Draw lots of text and a button.
	//Here is the text bit...
	glPushMatrix();
		glTranslatef(TITLE_POS);
		bitmapFontGLRenderText(gameData.SketchyFont, "Shooting", 1.0f);
		glTranslatef(TITLE_LINE2_OFFSET);
		bitmapFontGLRenderText(gameData.SketchyFont, "Practice", 1.0f);
		glTranslatef(TEXT_LINES_START);
		bitmapFontGLRenderText(gameData.MonospaceFont, "Copyright Daniel Bailey 2013-2014", 0.2f);
		glTranslatef(TEXT_MID_LINE_SPACE);
		bitmapFontGLRenderText(gameData.MonospaceFont, "C Programming assessment game", 0.2f);
		glTranslatef(TEXT_MID_LINE_SPACE);
		bitmapFontGLRenderText(gameData.MonospaceFont, "\"Orange Juice\" font available at:", 0.2f);
		glTranslatef(TEXT_MID_LINE_SPACE);
		bitmapFontGLRenderText(gameData.MonospaceFont, "http://www.dafont.com/orange-juice.font", 0.2f);
	glPopMatrix();


	//And here is the code for handling the button
	vector3 mouse = glWindowGetOGLPos(gameData.mousex, gameData.mousey);

	if (buttonIsHovered(&(gameData.ExitButton), mouse)){
		if (gameData.leftClick){
			reSetGameState(gs_Menu);
		}
		gameData.ExitButton.colour = COLOUR_WHITE;
	}
	else{
		gameData.ExitButton.colour = COLOUR_ONEPLAYER_BUTTON;
	}

	buttonDraw(&(gameData.ExitButton));
}

void initialiseGameState(gameState_t state){
	switch (state){
		case gs_Menu:initMenu(); break;
		case gs_OnePlay:initOnePlay(); break;
		case gs_TwoPlay:initTwoPlay(); break;
		case gs_Credits:initCredits(); break;
		case gs_Instructions:initInstructions(); break;
	}
}

void restartGameState(gameState_t state){
	switch (state){
		case gs_Menu:restartMenu(); break;
		case gs_OnePlay:restartOnePlay(); break;
		case gs_TwoPlay:restartTwoPlay(); break;
		case gs_Credits:restartCredits(); break;
		case gs_Instructions:restartInstructions(); break;
	}
}

void setGameState(gameState_t newState){
	gameData.gameState = newState;
	initialiseGameState(gameData.gameState);
	gameData.totTime = 0.0f;
}

void reSetGameState(gameState_t newState){
	gameData.gameState = newState;
	gameData.totTime = 0.0f;
	restartGameState(gameData.gameState);
}

//http://stackoverflow.com/questions/1952290/how-can-i-get-utctime-in-milisecond-since-january-1-1970-in-c-language
long int getTimeMilliSeconds(){
	struct timeval tp;
	gettimeofday(&tp, NULL);
	return (tp.tv_sec *1000) + (tp.tv_usec / 1000);
}

void drawGLWindow(){
	//draw stuff here
	float time_delta;
	long int thisDraw = getTimeMilliSeconds();
	time_delta = ((thisDraw - gameData.lastDraw)) /1000.0f;
	time_delta *= gameData.simSpeed;

	gameData.lastDraw = thisDraw;

	switch(gameData.gameState){
		case gs_Menu: drawGameMenu(time_delta); break;
		case gs_OnePlay: drawOnePlay(time_delta); break;
		case gs_TwoPlay: drawTwoPlay(time_delta); break;
		case gs_Credits: drawCredits(time_delta); break;
		case gs_Instructions: drawInstructions(time_delta); break;
	}

	if (gameData.leftClick){
		gameData.leftClick = false;
	}
}


void exitFunc(){
	//free up allocated memory before closing

	//free our projectile
	physObjFree(&(gameData.projectile));

	//free the data for the last level
	levelFree(&(gameData.levelData));

	//free the physics world
	physWorldFree(&(gameData.physWorld));
}

int main (int argc, char **argv) {

	//GLUT never returns and so the main function will not exit properly
	//To get arround this we need an exit function that is called just before the program exits
	//The following command registers this function
	atexit(exitFunc);

	glwindow_init(argc, argv); //create the 3D view window (freeglut)
	glwindow_setDrawFunc(drawGLWindow); //set the callback for the draw funcion

	//Set up freeGLUT Keyboard callbacks
	glwindow_setKeyboardFunc(keyboard);
	glwindow_setKeyboardSpecialFunc(keyboardSpecial);
	glwindow_setKeyboardSpecialUpFunc(keyboardSpecialUp);
	initKeyPressed();

	//Set up freeGLUT Mouse callbacks
	glwindow_setMotionFunc(motion);
	glwindow_setMouseFunc(mouse);

	gameData.simSpeed = 1.0f; //simulate physics in real time (one second per second)

	//glWindowData.zoomEnabled = true;
	//glWindowData.translateEnabled = true;
	//glWindowData.rotateEnabled = true;

	//the OpenGL maximum texture size may be smaller than some large images we need...
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &(gameData.maxDim));
	if (gameData.maxDim < 1024){
		printf("Texture limit is too small! Unable to load textures. Program will exit.\n");
		return 1;
	}

	//if the big font won't fit then we need to load a smaller version of it
	char *OrangeJuiceFontMapFile;
	if (gameData.maxDim < 4096){
		printf("Texture limit is too small! The sketchy font has been scaled down.\n");
		OrangeJuiceFontMapFile = MAIN_PROGRAM_SKETCHY_FONT_FILE_SMALL;
	}
	else{
		OrangeJuiceFontMapFile = MAIN_PROGRAM_SKETCHY_FONT_FILE_LARGE;
	}

	//load fonts
	gameData.MonospaceBitmap = bitmapLoad(MAIN_PROGRAM_MONOSPACE_FONT_FILE);	//Load each bitmap into memory
	gameData.MonospaceFont = bitmapToGLTexture(gameData.MonospaceBitmap);		//Copy each bitmap into an OpenGL texture
	bitmapFree(gameData.MonospaceBitmap);										//Free our copy of the bitmap

	//(same again, other font)
	gameData.SketchyBitmap = bitmapLoad(OrangeJuiceFontMapFile);
	gameData.SketchyFont = bitmapToGLTexture(gameData.SketchyBitmap);
	bitmapFree(gameData.SketchyBitmap);

	//Similar story for the grass texture
	gameData.grassBitmap = bitmapLoad(MAIN_PROGRAM_GRASS_TEXTURE);
	gameData.grassTexture = bitmapToGLTexture(gameData.grassBitmap);
	bitmapFree(gameData.grassBitmap);
	//we loaded one texture at a time to save memory usage when starting

	setGameState(gs_Menu); //Start with the main menu

	//last thing is to reset the time
	gameData.lastDraw = getTimeMilliSeconds();

	glwindow_show();//go!

	//The program never returns here!
	//To add code that you would expect to execute here, you must add it to the exitFunc().

	//The return statement should never be reached and so if it is, this is an error,
	//for this reason it returns non-zero to indicate an error
	return 1;
}
