/*
 * CommandStatus.h
 *
 *  Created on: Apr 12, 2023
 *      Author: Ryu
 */

#ifndef INC_COMMANDSTATUS_H_
#define INC_COMMANDSTATUS_H_

namespace controll
{
	enum status {Run,Normal_End,Forced_End,Abnormal_End,Break_End};
	class CommandStatus
	{
		enum status command_status=Normal_End;
	public:
		void off_command(enum status cs);//Statusをオフにする
		void on_command(enum status cs);//Statusをオンにする
		enum status show_status();//現在のStatusを返す
	};
}


#endif /* INC_COMMANDSTATUS_H_ */
