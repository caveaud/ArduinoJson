// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

#define SHOULD_WORK(expression) REQUIRE(DeserializationError::Ok == expression);
#define SHOULD_FAIL(expression) \
  REQUIRE(DeserializationError::TooDeep == expression);

TEST_CASE("JsonDeserializer nestingLimit") {
  DynamicJsonDocument doc(4096);

  SECTION("Input = const char*") {
    SECTION("limit = 0") {
      DeserializationOption::NestingLimit nestingLimit(0);
      SHOULD_WORK(deserializeJson(doc, "\"toto\"", nestingLimit));
      SHOULD_WORK(deserializeJson(doc, "123", nestingLimit));
      SHOULD_WORK(deserializeJson(doc, "true", nestingLimit));
      SHOULD_FAIL(deserializeJson(doc, "[]", nestingLimit));
      SHOULD_FAIL(deserializeJson(doc, "{}", nestingLimit));
      SHOULD_FAIL(deserializeJson(doc, "[\"toto\"]", nestingLimit));
      SHOULD_FAIL(deserializeJson(doc, "{\"toto\":1}", nestingLimit));
    }

    SECTION("limit = 1") {
      DeserializationOption::NestingLimit nestingLimit(1);
      SHOULD_WORK(deserializeJson(doc, "[\"toto\"]", nestingLimit));
      SHOULD_WORK(deserializeJson(doc, "{\"toto\":1}", nestingLimit));
      SHOULD_FAIL(deserializeJson(doc, "{\"toto\":{}}", nestingLimit));
      SHOULD_FAIL(deserializeJson(doc, "{\"toto\":[]}", nestingLimit));
      SHOULD_FAIL(deserializeJson(doc, "[[\"toto\"]]", nestingLimit));
      SHOULD_FAIL(deserializeJson(doc, "[{\"toto\":1}]", nestingLimit));
    }
  }

  SECTION("char* and size_t") {
    SECTION("limit = 0") {
      DeserializationOption::NestingLimit nestingLimit(0);
      SHOULD_WORK(deserializeJson(doc, "\"toto\"", 6, nestingLimit));
      SHOULD_WORK(deserializeJson(doc, "123", 3, nestingLimit));
      SHOULD_WORK(deserializeJson(doc, "true", 4, nestingLimit));
      SHOULD_FAIL(deserializeJson(doc, "[]", 2, nestingLimit));
      SHOULD_FAIL(deserializeJson(doc, "{}", 2, nestingLimit));
      SHOULD_FAIL(deserializeJson(doc, "[\"toto\"]", 8, nestingLimit));
      SHOULD_FAIL(deserializeJson(doc, "{\"toto\":1}", 10, nestingLimit));
    }

    SECTION("limit = 1") {
      DeserializationOption::NestingLimit nestingLimit(1);
      SHOULD_WORK(deserializeJson(doc, "[\"toto\"]", 8, nestingLimit));
      SHOULD_WORK(deserializeJson(doc, "{\"toto\":1}", 10, nestingLimit));
      SHOULD_FAIL(deserializeJson(doc, "{\"toto\":{}}", 11, nestingLimit));
      SHOULD_FAIL(deserializeJson(doc, "{\"toto\":[]}", 11, nestingLimit));
      SHOULD_FAIL(deserializeJson(doc, "[[\"toto\"]]", 10, nestingLimit));
      SHOULD_FAIL(deserializeJson(doc, "[{\"toto\":1}]", 12, nestingLimit));
    }
  }
}
