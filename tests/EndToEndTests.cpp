#include "gtest/gtest.h"
#include "Parser.h"
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string/predicate.hpp>

namespace fs = ::boost::filesystem;

class EndToEndTest : public ::testing::Test
{
public:
	void RunAllTigFilesInTestDirectory()
	{
		fs::path path(fs::system_complete("../../tests/TestPrograms"));
		fs::directory_iterator iter(path), eod;
		BOOST_FOREACH(fs::path const &p, std::make_pair(iter, eod))
		{
			if (is_regular_file(p) && boost::algorithm::ends_with(p.filename().string(), ".tig"))
			{
				Parser parser = Parser::CreateParserForFile(p.string());
				try
				{
					auto prog = parser.Parse();
                    prog->TypeCheck();
				}
				catch (const ParseException& t)
				{
					if (!boost::algorithm::ends_with(p.filename().string(), "49.tig"))
					{
						std::cout << t.what() << " thrown in " << p.filename().string() << "\n";
						FAIL();
					}
				}
				catch (...)
				{
					std::cout << "Failure in " << p.filename().string() << "\n";
					FAIL();
				}
			}
		}
	}
};

TEST_F(EndToEndTest, RunAll)
{
	RunAllTigFilesInTestDirectory();
}
