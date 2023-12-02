#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <sstream>

using namespace std;

//functions//

struct ProductData
{
	string Name, Amount, Price;
};

struct UserData
{
	string FirstName, LastName, UserName, Password, Type;
};

void InvalidFunction()
{
	cout << "---[ERROR: You have entered an invalid input, please only input the options stated.]---" << endl;
}

string AskUserInput(string question)
{
	cout << question;

	string input;

	getline(cin >> ws, input);
	return input;
}

bool AskUserConfirmation(string question)
{
	string response = AskUserInput(question);
	for (int i = 0; i < response.length(); i++) response[i] = toupper(response[i]);
	if (response == "YES") return true;
	return false;
}

UserData LoadUser(string FileName)
{
	UserData u;

	ifstream file("user" + FileName + ".txt");

	// Load data
	getline(file, u.FirstName);
	getline(file, u.LastName);
	getline(file, u.UserName);
	getline(file, u.Password);
	getline(file, u.Type);

	file.close();

	cout << "User file has been loaded!" << endl;

	return u;
}

UserData NewUser()
{
	cout << "[----------------------]" << endl;
	cout << "|Enlist a new user: |" << endl;
	cout << "[----------------------]" << endl;

	UserData user;

	cout << "[---------------------------------------]" << endl;
	user.FirstName = AskUserInput("First name of user: ");
	user.LastName = AskUserInput("Last name of user: ");
	user.UserName = AskUserInput("Username of user: ");
	user.Password = AskUserInput("Password of user: ");
	user.Type = AskUserInput("Type of user: ");
	cout << "[---------------------------------------]" << endl;

	return user;
}

void SaveUser(string FileName, UserData u)
{

	ofstream file("user" + FileName + ".txt");


	file << u.FirstName + '\n';
	file << u.LastName + '\n';
	file << u.UserName + '\n';
	file << u.Password + '\n';
	file << u.Type + '\n';

	file.close();

	cout << "File saved!" << endl;
}

void DisplayUserData(UserData u)
{
	cout << "[--------------------]\n";
	cout << "First Name:" + u.FirstName << endl;
	cout << "Last Name:" + u.LastName << endl;
	cout << "Username:" + u.UserName << endl;
	cout << "Password: " + u.Password << endl;
	cout << "Type: " + u.Type << endl;
	cout << "\n[--------------------]" << endl;
}

void AddUserFunction(bool PreviousFileCreated, string FileName, UserData& User)
{
	bool ValidInput;
	bool Save;
	system("cls");
	ValidInput = true;
	User = NewUser();
	UserData p;
	system("cls");
	cout << "[Details of User: ]" << endl;
	DisplayUserData(User);
	cout << "[-----------------------------------]" << endl;
	Save = AskUserConfirmation("Would you like to save your file? (Yes/No)\n");
	cout << "[-----------------------------------]" << endl;
	PreviousFileCreated;
	if (Save)
	{
		if (!PreviousFileCreated)
		{
			FileName = User.UserName;
		}

		SaveUser(FileName, User);
	}
}

void ModifyUserFunction(UserData& User)
{

	string FileName = AskUserInput("[-----------------------------------]\n|What is the Username of your user?: |\n[-----------------------------------]\n");
	system("cls");
	ifstream file("user" + FileName + ".txt");
	if (file)
	{
		User = LoadUser(FileName);
		DisplayUserData(User);
		while (true)
		{
			if (!AskUserConfirmation("Would you like to edit your data? (Yes/No)\n")) break;

			cout << "[-----------------------]" << endl;
			cout << "|Select data to edit|" << endl;
			cout << "[(1)First Name]\n[(2)Last Name]\n[(3)Username]\n[(4)Password]\n[(5)Type]\n" << endl;
			cout << "[-----------------------]" << endl;

			int ValidInput;
			cin >> ws >> ValidInput;
			system("cls");
			switch (ValidInput)
			{
			case 1:
				User.FirstName = AskUserInput("[-----------------]\n|First name of User: |\n[-----------------]\n");
				break;

			case 2:
				User.LastName = AskUserInput("[-----------------]\n[Last name of User: ]\n[-----------------]\n");
				break;

			case 3:
				User.UserName = AskUserInput("[-----------------]\n[Username of User: ]\n[-----------------]\n");
				break;

			case 4:
				User.Password = AskUserInput("[-----------------]\n[Password of User: ]\n[-----------------]\n");
				break;

			case 5:
				User.Type = AskUserInput("[-----------------]\n[Type of User: ]\n[-----------------]\n");
				break;

			default:
				InvalidFunction();
				continue;
			}

			DisplayUserData(User);
		}

		bool save = AskUserConfirmation("[-------------------------------]\n|Would you like to save your file? (Yes/No)|\n[-------------------------------]\n");
		bool previousFileCreated;
		string FileName;

		if (save)
		{
			if (!previousFileCreated)
			{
				FileName = User.UserName;
			}

			SaveUser(FileName, User);



		}

	}

	else
	{
		cout << "[The product specified does not exist.]\n[Please go back and ADD the product first.]" << endl;
	}

}

void RemoveUserFunction()
{
	int Status;
	char FileName[100];
	cout << "[-------------------------------------------------]" << endl;
	cout << "[Enter the name of the product to REMOVE/DELETE: ]" << endl;
	cout << "(Please put 'user' in the beginning\n and '.txt' at the end of the User Name\n for it to be successfully removed.)" << endl;
	cout << "[Example: userUserName.txt]" << endl;
	cout << "[-------------------------------------------------]" << endl;
	cin >> FileName;
	Status = remove(FileName);
	if (Status == 0)
	{
		cout << "[-------------------------------------------]" << endl;
		cout << "|User file has been deleted successfully!|" << endl;
		cout << "[-------------------------------------------]" << endl;
	}
	else
	{
		cout << "[------------------------------------------]" << endl;
		cout << "|User file was NOT deleted successfully.|" << endl;
		cout << "[------------------------------------------]" << endl;
	}
}

ProductData LoadProduct(string FileName)
{
	ProductData p;

	ifstream file(FileName + ".txt");

	// Load data
	getline(file, p.Name);
	getline(file, p.Amount);
	getline(file, p.Price);
	file.close();
	cout << "[----------------------------]" << endl;
	cout << "|Product file has been loaded!|" << endl;
	cout << "[----------------------------]" << endl;

	return p;
}

ProductData NewProduct()
{
	cout << "[----------------------]" << endl;
	cout << "|Enlist a new product: |" << endl;
	cout << "[----------------------]" << endl;

	ProductData product;

	cout << "[---------------------------------------]" << endl;
	product.Name = AskUserInput("Name of Product: ");
	product.Amount = AskUserInput("Quantity of Product: ");
	product.Price = AskUserInput("Price of Product: ");
	cout << "[---------------------------------------]" << endl;

	return product;
}

void SaveProduct(string FileName, ProductData p)
{

	ofstream file(FileName + ".txt");

	file << p.Name + '\n';
	file << p.Amount + '\n';
	file << p.Price + '\n';

	file.close();

	cout << "File saved!" << endl;
}

void SaveNewProductAmount(string FileName, ProductData& Product)
{
	ofstream file(FileName + ".txt");
	file << Product.Name + '\n';
	file << Product.Amount + '\n';
	file << Product.Price + '\n';
	file.close();
	cout << "File saved!" << endl;
}

void DisplayProductData(ProductData p)
{
	cout << "[--------------------]\n";
	cout << "Name of Product:" + p.Name << endl;
	cout << "Quantity of Product:" + p.Amount << endl;
	cout << "Price per Unit:" + p.Price << endl;
	cout << "\n[--------------------]" << endl;
}

bool LoginFunction(string AdminLogin, string AdminPassword)
{

	if (AdminLogin == "admin" && AdminPassword == "super")
	{
		cout << "Account logged in!" << endl;
		return true;
	}

	cout << "[The Username or the password does not match\n Please try again.]" << endl << endl;
	return false;
}

void AddProductFunction(bool PreviousFileCreated, string FileName, ProductData& Product)
{
	bool ValidInput;
	bool Save;
	system("cls");
	ValidInput = true;
	Product = NewProduct();
	ProductData p;
	system("cls");
	cout << "[Details of Product: ]" << endl;
	DisplayProductData(Product);
	cout << "[-----------------------------------]" << endl;
	Save = AskUserConfirmation("Would you like to save your file? (Yes/No)\n");
	cout << "[-----------------------------------]" << endl;
	PreviousFileCreated;
	if (Save)
	{
		if (!PreviousFileCreated)
		{
			FileName = Product.Name;
		}

		SaveProduct(FileName, Product);
	}
}

void ModifyProductFunction(ProductData& Product)
{

	string FileName = AskUserInput("[-----------------------------------]\n|What is the name of your product?: |\n[-----------------------------------]\n");
	system("cls");
	ifstream file(FileName + ".txt");
	if (file)
	{
		Product = LoadProduct(FileName);
		DisplayProductData(Product);
		while (true)
		{
			if (!AskUserConfirmation("Would you like to edit your data? (Yes/No)\n")) break;

			cout << "[-----------------------]" << endl;
			cout << "|Select data to edit|" << endl;
			cout << "[(1)Name]\n[(2)Amount]\n[(3)Price]\n" << endl;
			cout << "[-----------------------]" << endl;

			int ValidInput;
			cin >> ws >> ValidInput;
			system("cls");
			switch (ValidInput)
			{
			case 1:
				Product.Name = AskUserInput("[-----------------]\n|Name of Product: |\n[-----------------]\n");
				break;

			case 2:
				Product.Amount = AskUserInput("[-----------------]\n[Quantity of Product: ]\n[-----------------]\n");
				break;

			case 3:
				Product.Price = AskUserInput("[-----------------]\n[Price of Product: ]\n[-----------------]\n");
				break;


			default:
				InvalidFunction();
				continue;
			}

			DisplayProductData(Product);
		}

		bool save = AskUserConfirmation("[-------------------------------]\n|Would you like to save your file? (Yes/No)|\n[-------------------------------]\n");
		bool previousFileCreated;
		string FileName;

		if (save)
		{
			if (!previousFileCreated)
			{
				FileName = Product.Name;
			}

			SaveProduct(FileName, Product);



		}

	}

	else
	{
		cout << "[The product specified does not exist.]\n[Please go back and ADD the product first.]" << endl;
	}

}

void RemoveProductFunction()
{
	int Status;
	char FileName[100];
	cout << "[-------------------------------------------------]" << endl;
	cout << "[Enter the name of the product to REMOVE/DELETE: ]" << endl;
	cout << "(Please put '.txt' at the end of the Product Name\n for it to be successfully removed.)" << endl;
	cout << "[Example: ProductName.txt]" << endl;
	cout << "[-------------------------------------------------]" << endl;
	cin >> FileName;
	Status = remove(FileName);
	if (Status == 0)
	{
		cout << "[-------------------------------------------]" << endl;
		cout << "|Product file has been deleted successfully!|" << endl;
		cout << "[-------------------------------------------]" << endl;
	}
	else
	{
		cout << "[------------------------------------------]" << endl;
		cout << "|Product file was NOT deleted successfully.|" << endl;
		cout << "[------------------------------------------]" << endl;
	}
}

void AvailabilityProductFunction(ProductData Product)
{

	string FileName = AskUserInput("[-----------------------------------]\n|What is the name of your product?: |\n[-----------------------------------]\n");
	system("cls");
	ifstream file(FileName + ".txt");
	if (file)
	{
		Product = LoadProduct(FileName);
		DisplayProductData(Product);
	}
	else
	{
		cout << "[The product specified does not exist.]\n[Please go back and ADD the product first.]" << endl;
	}

}

void SaleProductFunction(ProductData& Product)
{
	int subtrahend;
	string FileName = AskUserInput("[-----------------------------------]\n|What is the name of your product?: |\n[-----------------------------------]\n");
	system("cls");
	ifstream file(FileName + ".txt");
	getline(file, Product.Amount);
	getline(file, Product.Price);
	file.close();
	if (file)
	{
		int diff;
		Product = LoadProduct(FileName);
		cout << "Amount of Product being Sold: ";
		cin >> subtrahend;
		int TotalPrice;
		int minuend = stoi(Product.Amount);
		int total = stoi(Product.Price);
		diff = minuend - subtrahend;
		TotalPrice = subtrahend * total;
		cout << "Total Price of Sale: " << TotalPrice << endl;
		cout << "Amount of Product left: " << diff << endl;
		to_string(diff) = (Product.Amount);
		SaveNewProductAmount(FileName, Product);
	}
	else
	{
		cout << "[The product specified does not exist.]\n[PLEASE CONTACT YOUR LOCAL ADMIN.]" << endl;
	}

}

int main()
{
	//Declarations//
	system("Color 6");
	ProductData Product;
	UserData User;
	int OptionSelect;
	string AdminLogin = "", AdminPassword = "", UserSelect = "", FileName = "", UsernameLogin = "", PasswordLogin = "";
	bool LoginVerified = false;
	bool Save;
	bool PreviousFileCreated;
	//start//

	bool ValidInput = false;
	do
	{
		cout << "[----------------------------------------------------------------------------------------------------------------------]" << endl;
		cout << "|-----------------------[Good day, welcome to the Sales System press [1] to PROCEED and [2] to EXIT.]------------------|" << endl;
		cout << "[----------------------------------------------------------------------------------------------------------------------]" << endl;
		cin >> OptionSelect;
		system("cls");
		switch (OptionSelect)
		{
		case 1: //mainmenusection

			ValidInput = false;
			do
			{
				cout << "[----------------------------------------------------------------------------------------------------------------------]" << endl;
				cout << "|-------------------------------------------[Select the following mode: ] ---------------------------------------------|\n[(1) ADMINISTRATOR MODE]\n[(2) CASHIER MODE]\n[(3) BACK]" << endl;
				cout << "[----------------------------------------------------------------------------------------------------------------------]" << endl;
				cin >> OptionSelect;
				system("cls");
				switch (OptionSelect)
				{
				case 1: //adminmode
					do
					{
						cout << "[----------------------------------------------------------------]" << endl;
						cout << "|You have chosen ADMIN mode]\n [Please fill in your credentials: |\n [USERNAME: ]\n [PASSWORD: ]\n [OR type 'BACK' in 'USERNAME' to LOGOUT.]" << endl;
						cout << "[----------------------------------------------------------------]" << endl;
						cout << "USERNAME: ";
						cin >> AdminLogin;
						if (AdminLogin == "BACK")
						{
							system("cls");
							bool LoginVerified = true;
							return main();
							break;
						}
						else if (AdminLogin != "BACK")
						{
							cout << "PASSWORD: ";
							cin >> AdminPassword;
							system("cls");
							LoginVerified = LoginFunction(AdminLogin, AdminPassword);
						}
					} while (!LoginVerified);
					//user inputs name and password.
					//program does check (through function most likely).
					//user can also type "BACK" to go back.
					// if string == (BACK) then execute return protocol, else login check.
					//(success!)
					ValidInput = false;
					do
					{
						cout << "[----------------------------------------------]" << endl;
						cout << "|Good day, admin. What would you like to do?: |\n[(1)Product Operations]\n[(2)User Operations]\n[(3) Logout]" << endl;
						cout << "[----------------------------------------------]" << endl;
						cin >> OptionSelect;
						system("cls");
						if (OptionSelect == 1)
						{
							//[add, modify, or remove a product on the system.]
							//user inputs type of operation.
							//chooses product operation
							//(success!)
							ValidInput = false;
							do
							{
								cout << "[You have chosen Product Operations.]\n [Please select an operation: ]\n [(1) Add a product]\n [(2) Modify a product]\n [(3) Remove a product]\n [(4) LOGOUT]\n " << endl;
								cin >> OptionSelect;
								system("cls");
								switch (OptionSelect)
								{
								case 1:
									AddProductFunction(PreviousFileCreated, FileName, Product);
									DisplayProductData(Product);
									break; //addproductfunc success!
								case 2:
									ModifyProductFunction(Product);
									break; //modifyproductfunc success!
								case 3:
									RemoveProductFunction();
									break; //removeproductfunc success!
								case 4:
									return main();
									break;
								default:
									InvalidFunction();
									break;
								}

							} while (ValidInput == false);
							break;
						}
						else if (OptionSelect == 2)
						{
							ValidInput = false;
							do
							{
								//Can add, modify, or remove a user on the system (not yet done.)
								cout << "[You have chosen User Operations.]\n [Please select an operation: ]\n [(1) Add a user]\n [(2) Modify a user's data]\n [(3) Remove a user]\n [(4) LOGOUT]\n " << endl;
								cin >> OptionSelect;
								system("cls");
								switch (OptionSelect)
								{
								case 1:
									AddUserFunction(PreviousFileCreated, FileName, User);
									break;  //adduserfunc success!
								case 2:
									ModifyUserFunction(User);
									break; //modifyuserfunc success!
								case 3:
									RemoveUserFunction();
									break; //removeuserfunc success!
								case 4:
									return main();
									break;
								default:
									InvalidFunction();
									break;
								}
								break;
							} while (ValidInput == false);
						}
						else if (OptionSelect == 3)
						{
							return main();
							break;
						}
						else
						{
							InvalidFunction();
							break;
						}

					} while (ValidInput == false);
					break;

				case 2: //cashiermode
					ValidInput = true;
					{
						ValidInput = false;
						do
						{

							cout << "[-------------------------------------------------------------------]" << endl;
							cout << "|[You have chosen CASHIER mode]\n [Please fill in your credentials: |\n [USERNAME: ]\n [PASSWORD: ]\n [OR type 'BACK' in 'USERNAME' to LOGOUT.]" << endl;
							cout << "[-------------------------------------------------------------------]" << endl;
							cout << "USERNAME: ";
							cin >> UsernameLogin;
							system("cls");
							ifstream file("user" + UsernameLogin + ".txt");
							getline(file, User.FirstName);
							getline(file, User.LastName);
							getline(file, User.UserName);
							getline(file, User.Password);
							getline(file, User.Type);
							file.close();
							if (file)
							{
								cout << "Account found!" << endl << endl;
								cout << "PASSWORD: ";
								cin >> PasswordLogin;
								if (PasswordLogin == User.Password)
								{
									system("cls");
									cout << "[--------------]" << endl;
									cout << "|login success!|" << endl;
									cout << "[--------------]" << endl << endl;
									ValidInput = false;
									do
									{
										cout << "[------------------------------------------------]" << endl;
										cout << "|Good day, cashier. What would you like to do?: |\n[(1)Start A Sale]\n[(2)Check availability of Product]\n[(3) Logout]" << endl;
										cout << "[------------------------------------------------]" << endl;
										cin >> OptionSelect;
										system("cls");
										switch (OptionSelect)
										{
										case 1:
											SaleProductFunction(Product);
											break;
										case 2:
											AvailabilityProductFunction(Product);
											break;
										default:
											return main();
											break;
										}

									} while (ValidInput == false);

								}
								else
								{
									cout << "[------------------------------------]" << endl;
									cout << "|password for account is not correct.|" << endl;
									cout << "[------------------------------------]" << endl;
								}
							}
							else
							{
								cout << "[---------------------------]" << endl;
								cout << "|Account has not been made.|\n |PLEASE CONTACT YOUR LOCAL ADMIN.|" << endl;
								cout << "[---------------------------]" << endl;
							}

						} while (ValidInput == false);
					}

					break;

				case 3: //backfunction
					ValidInput = true;
					return main();
					break;

				default: //invfunction
					InvalidFunction();
					break;
				}

			} while (ValidInput == false);
			break;

		case 2:

			ValidInput = true;
			cout << "[------------------------------------------------------------------------]" << endl;
			cout << "|Thank you for using the Sales System, have a wonderful rest of your day.|" << endl;
			cout << "[------------------------------------------------------------------------]" << endl;
			return 0;
			break;

		default:
			InvalidFunction();
			return main();
			break;

		}

	} while (ValidInput == false);

}




