#ifndef COLOR_H_
#define COLOR_H_

namespace color
{
  enum class Enum
  {
    BLACK,
    RED,
    GREEN,
    BLUE,
    WHITE,
    YELLOW,

    UNKNOWN
  };

  /// Converts a given \a key to the corresponding \ref color::Enum.
  constexpr Enum KeyToEnum(unsigned int key)noexcept;

  /// Converts any of the \ref color::Enum values into a string literal.
  const char* ToString(Enum value)noexcept;

  //----------------------------------------------------------------------------------------------
  //----------------------------------------------------------------------------------------------

  constexpr Enum KeyToEnum(unsigned int key)noexcept
  {
    return {static_cast<Enum>(key)};
  }

  const char* ToString(Enum value)noexcept
  {
#define IMPLEMENT_CASE(value, str) case value:   return #str

    switch (value)
    {
      IMPLEMENT_CASE(Enum::BLACK, BLACK);
      IMPLEMENT_CASE(Enum::RED, RED);
      IMPLEMENT_CASE(Enum::GREEN, GREEN);
      IMPLEMENT_CASE(Enum::BLUE, BLUE);
      IMPLEMENT_CASE(Enum::WHITE, WHITE);
      IMPLEMENT_CASE(Enum::YELLOW, YELLOW);
      IMPLEMENT_CASE(Enum::UNKNOWN, UNKNOWN);
    }

    return "Unhandled color";

#undef IMPLEMENT_CASE
  }
} // namespace color

#endif // COLOR_H_