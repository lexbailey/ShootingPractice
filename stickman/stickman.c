#include "stickman.h"

void stickManSetPose(stickman_t* man, pose_t pose){
	//change the pose variable
	man->pose = pose;

	//decide on the drop based on the stance (when firing, the stickman is slightly lower)
	float firePoseDrop = man->pose == ptStand? 0.0f : -FIREDROP;

	//one half of the stance width is the distance each limb is away from the body
	float halfStance = (STANCEWIDTH/2);

	//Here are the coordinates that can now be set up the same way for both stances
	man->bottom.x = man->pos.x;
	man->bottom.y = man->pos.y + LEGEIGHT + firePoseDrop;
	man->bottom.z = man->pos.z;

	man->top.x = man->pos.x;
	man->top.y = man->pos.y + LEGEIGHT+BODYHEIGHT  + firePoseDrop;
	man->top.z = man->pos.z;

	man->leftKnee.y = man->pos.y+(LEGEIGHT/2);
	man->leftKnee.z = man->pos.z;

	man->leftFoot.y = man->pos.y;
	man->leftFoot.z = man->pos.z;

	man->rightKnee.y = man->pos.y+(LEGEIGHT/2);
	man->rightKnee.z = man->pos.z;

	man->rightFoot.y = man->pos.y;
	man->rightFoot.z = man->pos.z;

	man->leftElbow.z = man->top.z;
	man->leftHand.z = man->top.z;
	man->rightElbow.z = man->top.z;
	man->rightHand.z = man->top.z;

	//some coordinates are particular to the stance
	if (man->pose == ptStand){

		man->leftKnee.x = man->pos.x-halfStance;
		man->leftFoot.x = man->pos.x-halfStance;

		man->rightKnee.x = man->pos.x+halfStance;
		man->rightFoot.x = man->pos.x+halfStance;

		/*
		man->leftElbow.x = man->top.x-halfStance;
		man->leftElbow.y = man->top.y-(ARMLENGTH/2);

		man->leftHand.x = man->top.x-halfStance;
		man->leftHand.y = man->top.y-ARMLENGTH;

		man->rightElbow.x = man->top.x+halfStance;
		man->rightElbow.y = man->top.y-(ARMLENGTH/2);

		man->rightHand.x = man->top.x+halfStance;
		man->rightHand.y = man->top.y-ARMLENGTH;
		*/
		man->leftElbow.x = 0.0f-halfStance;
		man->leftElbow.y = man->pos.y-(ARMLENGTH/2);

		man->leftHand.x =0.0f-halfStance;
		man->leftHand.y = man->pos.y-ARMLENGTH;

		man->rightElbow.x = 0.0f+halfStance;
		man->rightElbow.y = man->pos.y-(ARMLENGTH/2);

		man->rightHand.x = 0.0f+halfStance;
		man->rightHand.y = man->pos.y-ARMLENGTH;

	}

	if (man->pose == ptFire){

		man->leftKnee.x = man->pos.x;
		man->leftFoot.x = man->pos.x-(STANCEWIDTH/3);

		man->rightKnee.x = man->pos.x+(STANCEWIDTH/1.5f);
		man->rightFoot.x = man->pos.x+(STANCEWIDTH/1.5f);

		/*man->leftElbow.x = man->top.x-(ARMLENGTH/2);
		man->leftElbow.y = man->top.y-(ARMDROP);

		man->leftHand.x = man->top.x;
		man->leftHand.y = man->top.y-ARMDROP;

		man->rightElbow.x = man->top.x+(ARMLENGTH/2);
		man->rightElbow.y = man->top.y-(ARMDROP);

		man->rightHand.x = man->top.x+ARMLENGTH;
		man->rightHand.y = man->top.y-ARMDROP;
		*/

		man->leftElbow.x = 0.0f-(ARMLENGTH/2);
		man->leftElbow.y = man->pos.y-(ARMDROP);

		man->leftHand.x = 0.0f;
		man->leftHand.y = man->pos.y-ARMDROP;

		man->rightElbow.x = 0.0f+(ARMLENGTH/2);
		man->rightElbow.y = man->pos.y-(ARMDROP);

		man->rightHand.x = 0.0f+ARMLENGTH;
		man->rightHand.y = man->pos.y-ARMDROP;
	}

	//the head can also be set the same
	man->head.x = man->top.x;
	man->head.y = man->top.y+HEADRADIUS;
	man->head.z = man->top.z;
}

void stickManDraw(stickman_t *man){

	//set the colour
	colourEnable(man->colour);

	//draw the bottom half of the stickman (body and legs)
	drawFuncLine(man->top, man->bottom);
	drawFuncLine(man->bottom, man->leftKnee);
	drawFuncLine(man->bottom, man->rightKnee);
	drawFuncLine(man->leftKnee, man->leftFoot);
	drawFuncLine(man->rightKnee, man->rightFoot);

	//Draw the head
	drawFuncCircle(man->head, HEADRADIUS, 30);

	glPushMatrix();
		//Move to the top of the stickman
		drawFuncApplyTranslation(man->top);
		if (man->pose == ptFire){
			//If we are aiming then rotate to point the right way
			glRotatef(man->aimAngle, 0,0,1);

			//limit pull back factor (dont pull the bow too far)
			if (man->pullBack > PULLBACKLIMIT){	man->pullBack = PULLBACKLIMIT; }
		}

		vector3 leftHandTrans, bowArcCentre;

		//Setting up the left hand (for pulling the bow)...
		leftHandTrans.y = man->leftHand.y;
		leftHandTrans.z = man->leftHand.z;
		bowArcCentre.y = man->leftHand.y;
		bowArcCentre.z = man->leftHand.z;
		if (man->pose == ptFire){
			//Move the left hand back by as far as the bow is pulled back
			leftHandTrans.x = man->leftHand.x - man->pullBack;
			//Move the centre of the circle that the arc is on forward
			bowArcCentre.x = man->leftHand.x + man->pullBack;
		}
		else{
			//When not firing, hand is in normal position
			leftHandTrans.x = man->leftHand.x;
			//this makes no difference really as the bow is only drawn in fire mode
			bowArcCentre.x = man->leftHand.x;
		}

		//Calculate the distance to the right hand (which holds the bow)
		//This is to get the circle distance correct
		float distance = man->rightHand.x - bowArcCentre.x;

		//Draw the arms!
		drawFuncLine(vector3GetNull(), (man->leftElbow));
		drawFuncLine(vector3GetNull(), (man->rightElbow));

		drawFuncLine((man->leftElbow), (leftHandTrans));
		drawFuncLine((man->rightElbow), (man->rightHand));

		//If we are in fire mode, draw the bow
		if (man->pose == ptFire){
			colourEnable(BOW_COLOUR); //set the bow colour
			vector3 startPos, stopPos;
			drawFuncArcResult(bowArcCentre, distance, 30, 60, 120, &startPos, &stopPos);
			drawFuncLine(startPos, leftHandTrans);
			drawFuncLine(stopPos, leftHandTrans);
		}

	glPopMatrix();
}

