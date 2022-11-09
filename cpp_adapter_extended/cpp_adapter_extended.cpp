//based off refactoring guru example

#include <iostream>
#include <string>
#include <vector>

class Analyzer {
private:
	std::vector<float> cdata;
public:
	Analyzer(std::vector<float> &basevector)
	{
		cdata = basevector;
	}
	void Analyze(float &min, float &max)
	{
		if (cdata.size() > 0)
		{
			min = cdata[0];
			max = cdata[0];
			for (float a : cdata)
			{
				if (a < min) min = a;
				if (a > max) max = a;
			}
		}
	}
};

//regular target class
class Target {
public:
	virtual ~Target() = default;

	virtual std::string Request() const {
		return "Target: The default target's behavior.";
	}
} target;

//unique class that does not fit with Target's interface
class UniqueTarget {
public:
	std::string SpecificRequest() const {
		return ".eetpadA eht fo roivaheb laicepS";
	}
} uniqueTarget;

//adapter calss that can link incompatible interfaces
//MUST BE INHERITED FROM TARGET
class Adapter : public Target {
private:
	UniqueTarget *uTarg_;

public:
	Adapter(UniqueTarget *adaptee) : uTarg_(adaptee) {}

	std::string Request() const override {
		std::string to_reverse =
			this->uTarg_->SpecificRequest();
		std::reverse(to_reverse.begin(), to_reverse.end());
		return "Adapter: (TRANSLATED) " + to_reverse;
	}
};

//analyzer adapter class
class AnAdapter : public Target {
private:
	Analyzer *analyzer_;

public:
	AnAdapter(Analyzer *adaptee) : analyzer_(adaptee) {}

	std::string Request() const override {
		std::string response = "";
		float mn = 0; float mx = 0;
		analyzer_->Analyze(mn, mx);
		response += "min = " + std::to_string(mn);
		response += "; max = " + std::to_string(mx);
		return "Data from analyzer: " + response;
	}
};


//client class
class Client
{
public:
	void ClientCode(const Target *target) {
		std::cout << target->Request();
	}
} ourClient;

int main() {

	std::vector<float> testData = { 0, 3, 7, 12, 18, 93 };
	Analyzer * testAnalyzer = new Analyzer(testData);

	std::cout << "Client: I can work just fine with the Target objects:\n";

	ourClient.ClientCode(&target);

	std::cout << "\n\n";

	std::cout << "Client: The Adaptee class has a weird interface. See, I don't understand it:\n";
	std::cout << "Adaptee: " << uniqueTarget.SpecificRequest();
	std::cout << "\n\n";
	std::cout << "Client: But I can work with it via the Adapter:\n";

	Adapter *adapter = new Adapter(&uniqueTarget);
	ourClient.ClientCode(adapter);

	std::cout << "\n";

	AnAdapter *anadapter = new AnAdapter(testAnalyzer);
	ourClient.ClientCode(anadapter);

	std::cout << "\n";

	delete adapter;
	delete anadapter;
	delete testAnalyzer;

	return 0;
}
