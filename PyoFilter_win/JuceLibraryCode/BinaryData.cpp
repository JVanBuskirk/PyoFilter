/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

namespace BinaryData
{

//================== pyoFilter.py ==================
static const unsigned char temp_binary_data_0[] =
"snd = Input([0, 1])\r\n"
"\r\n"
"cfreq = SigTo(440, 0.05, 440)\r\n"
"q = SigTo(5, 0.05, 5)\r\n"
"\r\n"
"filter = Reson(snd, freq=cfreq, q=q).out()\r\n"
"\r\n"
"out = Mix(filter, voices=2).out()";

const char* pyoFilter_py = (const char*) temp_binary_data_0;


const char* getNamedResource (const char*, int&) throw();
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes) throw()
{
    unsigned int hash = 0;
    if (resourceNameUTF8 != 0)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0xec92574a:  numBytes = 158; return pyoFilter_py;
        default: break;
    }

    numBytes = 0;
    return 0;
}

const char* namedResourceList[] =
{
    "pyoFilter_py"
};

}
