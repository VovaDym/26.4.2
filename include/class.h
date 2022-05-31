#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>

class Phone
{
	class Contact
	{
		std::string name;
		std::vector <std::string> numbers;
	public:
		Contact(const std::string& newName, const std::string& newNumber)
		{
			setName(newName);
			setPhone(newNumber);
		}
		std::string getName()
		{
			return name;
		}
		
		void getPhoneNumbers(std::vector <std::string>& vec)
		{
			vec = numbers;
		}

		void setName(const std::string& newName)
		{
			name = newName;
		}
		void setPhone(const std::string& newNumber)
		{
			numbers.push_back(newNumber);
		}
	};
	std::map <std::string, Contact> abNameContact;
	std::map <std::string, std::string> abPhoneName;

	std::map <std::string, int> commands = { {"add", 0}, {"call", 1}, {"sms", 2}, {"exit", 3} };

	void smsEnter(std::string& number)
	{
		std::string message;
		std::cout << "Enter a message:";
		std::cin.ignore();
		std::getline(std::cin, message);

		
		std::cout << "Sending sms to number " << number << " ... " << std::endl;
		std::cout << "Message: " << message << std::endl << std::endl;
	}

	bool isPhoneNumber(const std::string& str)
	{
		if (str.size() != 12 || str[0] != '+' || str[1] != '7')
		{
			return false;
		}	
		for (int i = 2; i < str.size(); ++i)
		{
			if (!isdigit(str[i]))
			{
				return false;
			}		
		}		
		return true;
	}

	bool isPhoneNumberExist(const std::string& n)
	{
		return (abPhoneName.find(n) != abPhoneName.end());
	}

public:

	int chosenCommand()
	{
		std::cout << "Enter a command from the list:" << std::endl;
		for (const auto c : commands)
		{
			std::cout << "  " << c.first << ';' << std::endl;
		}	
		std::string enteredCommand;
		std::map <std::string, int>::iterator itf;
		do
		{
			std::cin >> enteredCommand;
			itf = commands.find(enteredCommand);
			if (itf == commands.end())
			{
				std::cout << "Incorrect command. Try again" << std::endl;
			}	
		} while (itf == commands.end());

		return itf->second;
	}
	
	void add()
	{
		system("cls");
		std::string number;
		std::string name;
		std::cout << "Enter contact name: " << std::endl;
		
		std::cin >> name;
		std::cout << "Enter phone number on format +7xxxxxxxxxx: ";
		do
		{
			std::cin >> number;
			if (!isPhoneNumber(number))
			{
				std::cout << "Incorrect phone number format. Try again" << std::endl;
			}
				
			if (isPhoneNumberExist(number))
			{
				std::cout << "This phone number exist. Enter new phone number" << std::endl;
			}		
		} while (!isPhoneNumber(number) || isPhoneNumberExist(number));

		std::map <std::string, Contact>::iterator itf = abNameContact.find(name);
		if (itf == abNameContact.end())
		{
			Contact newContact(name, number);
			abNameContact.insert(std::pair <std::string, Contact>(name, newContact));

			std::cout << "New contact created" << std::endl;
		}
		else
		{
			itf->second.setPhone(number);

			std::cout << "Phone was added to person: " << itf->first << std::endl << std::endl;
		}
		abPhoneName.insert(std::pair <std::string, std::string>(number, name));
	}

	void call()
	{
		system("cls");

		std::string data;
		std::cout << "Enter name of contact or phone number to call: ";
		std::cin >> data;

		system("cls");
		
		if (isPhoneNumber(data))
		{
			if (isPhoneNumberExist(data))
			{	
				std::map <std::string, std::string>::iterator itf = abPhoneName.find(data);
				if (itf != abPhoneName.end())
				{
					
					std::cout << "Calling " << data << " ... " << " contact: " << itf-> second <<std::endl << std::endl;
				}
				else
				{
					std::cout << "Contact with the number " << data << " not found" << std::endl << std::endl;
				}	
			}
			else
			{
				std::cout << data << " phone number doesn't exist " << std::endl << std::endl;
			}		
		}
		else
		{
			std::map <std::string, Contact>::iterator itf = abNameContact.find(data);
			if (itf != abNameContact.end())
			{
				std::vector <std::string> phoneNumbers;
				itf->second.getPhoneNumbers(phoneNumbers);
				if (phoneNumbers.size() > 1)
				{
					std::cout << "Select the number you need" << std::endl;
					std::cout << "Enter the serial number of the contact's phone numbers. 1 or > ..." << std::endl;
					int numPhone = 0;
					for (const auto& p : phoneNumbers)
					{
						std::cout << "  " << numPhone + 1 << ". " << p << ";" << std::endl;
						++numPhone;
					}
					int call;
					do
					{
						std::cin >> call;
						if (call <= 0 || call > numPhone)
						{
							std::cout << "Incorrect phone position number. Try again" << std::endl << std::endl;
						}
							
					} while (call <= 0 || call > numPhone);

					--call;
					system("cls");

					std::cout << "Calling " << phoneNumbers[call] << " contact: " << itf->first << std::endl << std::endl;
				}
				else
				{
					std::cout << "Calling " << phoneNumbers[0] << " contact: " << itf->first << std::endl << std::endl;
				}	
			}
			else
			{
				std::cout << "Contact " << data << " not found" << std::endl << std::endl;
			}		
		}
	}

	void sms()
	{
		system("cls");

		std::string data;
		std::string message;
		std::cout << "Enter name of contact or phone number to send sms: ";
		std::cin >> data;
		if (isPhoneNumber(data))
		{
			if (isPhoneNumberExist(data))
			{
				smsEnter(data);
			}
			else
			{
				std::cout << data << "Phone number doesn't exist" << std::endl << std::endl;
			}		
		}
		else
		{
			system("cls");
			std::map <std::string, Contact>::iterator itf = abNameContact.find(data);
			if (itf != abNameContact.end())
			{
				std::vector <std::string> phoneNumbers;
				itf->second.getPhoneNumbers(phoneNumbers);
				if (phoneNumbers.size() > 1)
				{
					std::cout << "Select the number you need" << std::endl;
					std::cout << "Enter the serial number of the contact's phone numbers. 1 or > ..." << std::endl;
					int numPhone = 0;
					for (const auto& p : phoneNumbers)
					{
						std::cout << "  " << numPhone + 1 << ". " << p << ";" << std::endl;
						++numPhone;
					}
					int num;
					do
					{
						std::cin >> num;
						if (num <= 0 || num > numPhone)
							std::cout << "Incorrect phone number. Try again" << std::endl << std::endl;
					} while (num <= 0 || num > numPhone);

					--num;

					smsEnter(phoneNumbers[num]);
				}
				else
				{
					smsEnter(phoneNumbers[0]);
				}		
			}
			else
			{
				std::cout << "Contact with this data not found" << std::endl << std::endl;
			}		
		}
	}
};

