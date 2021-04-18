#include <libio/BufReader.h>
#include <libio/NumberScanner.h>
#include <libio/Streams.h>
#include <libxml/Parser.h>

#include <libgraphic/rast/Rasterizer.h>
#include <libgraphic/svg/Svg.h>

ResultOr<RefPtr<Graphic::Bitmap>> Graphic::Svg::render(IO::Reader &reader, int size_hint)
{
    IO::BufReader buf{reader, 512};
    auto doc = TRY(Xml::parse(buf));

    if (doc.root().name() != "svg")
    {
        logger_error("Svg file must begin with svg root element");
        return Result::ERR_INVALID_DATA;
    }
    auto dec_scanner = IO::NumberScanner::decimal();

    int width = 16;
    int height = 16;

    // Width attribute
    {
        auto width_reader = IO::MemoryReader(doc.root().attributes()["width"]);
        auto width_scanner = IO::Scanner(width_reader);
        width = dec_scanner.scan_int(width_scanner).unwrap();
    }

    // Height attribute
    {
        auto height_reader = IO::MemoryReader(doc.root().attributes()["height"]);
        auto height_scanner = IO::Scanner(height_reader);
        height = dec_scanner.scan_int(height_scanner).unwrap();
    }

    float scale = 1;

    if (size_hint > 0)
    {
        scale = (float)size_hint / MAX(width, height);
    }

    auto bitmap = TRY(Bitmap::create_shared(width * scale, height * scale));
    bitmap->clear(Colors::TRANSPARENT);
    bitmap->filtering(BitmapFiltering::NEAREST);
    Rasterizer rast{bitmap};

    for (auto child : doc.root().children())
    {
        if (child.name() == "path")
        {
            Color fillColor = Colors::BLACK;
            if (child.attributes().has_key("fill"))
            {
                fillColor = Color::parse(child.attributes()["fill"]);
            }

            auto path = Graphic::Path::parse(child.attributes()["d"].cstring());
            rast.fill(path, Math::Mat3x2f::scale(scale), Graphic::Fill{fillColor});
        }
        else
        {
            IO::logln("Unhandled svg node: %s", child.name());
        }
    }

    return bitmap;
}