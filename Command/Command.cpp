#include<iostream>
#include<memory>
#include<vector>

// Receiver
class Document
{
public:
	void Save() const
	{
		std::cout << "Document saved." << std::endl;
	}

	void Open() const
	{
		std::cout << "Document opened." << std::endl;
	}
};

class ICommand
{
public:
	virtual ~ICommand() = default;
	virtual void Execute() const = 0;
};

class SaveCommand : public ICommand
{
public:
	explicit SaveCommand(std::shared_ptr<Document> doc) : document(doc) {}
	void Execute() const override
	{
		document->Save();
	}
private:
	std::shared_ptr<Document> document;
};

class OpenCommand : public ICommand
{
public:
	explicit OpenCommand(std::shared_ptr<Document> doc) : document(doc) {}	
	void Execute() const override
	{
		document->Open();
	}
private:
	std::shared_ptr<Document> document;
};

// Invoker
class Button
{
public:
	explicit Button(std::shared_ptr<ICommand> cmd) : command(cmd) {}
	void Click()
	{
		command->Execute();
	}
private:
	std::shared_ptr<ICommand> command;
};

int main()
{
	auto doc = std::make_shared<Document>();
	auto saveCommand = std::make_shared<SaveCommand>(doc);
	auto openCommand = std::make_shared<OpenCommand>(doc);

	Button saveButton(saveCommand);
	Button openButton(openCommand);

	saveButton.Click();
	openButton.Click();
}