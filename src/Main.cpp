#include "Parser.h"
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string/predicate.hpp>

namespace fs = ::boost::filesystem;
using namespace std;
using namespace AST;

	void RunAllTigFilesInTestDirectory()
	{
		fs::path path(fs::system_complete("../tests/TestPrograms"));
		fs::directory_iterator iter(path), eod;
		BOOST_FOREACH(fs::path const &p, std::make_pair(iter, eod))
		{
			if (is_regular_file(p) && boost::algorithm::ends_with(p.filename().string(), "12.tig"))
			{
				std::unique_ptr<std::istream> stream = make_unique<std::ifstream>(p.string(), std::ifstream::in);
				Parser parser(TokenStream(std::move(stream)));
				try
				{
					parser.Parse();
				}
				catch (const std::exception& t)
				{
					std::cout << t.what() << " thrown in " << p.filename().string() << "\n";
				}
				catch (...)
				{
					std::cout << "wtf in " << p.filename().string() << "\n";
				}
			}
		}
	}

int main()
{
	RunAllTigFilesInTestDirectory();
}
