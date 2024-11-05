from curl_cffi import requests

URL = "https://neal.fun/api/infinite-craft/pair"

MAX_TRIES = 5

HEADERS = {
  "User-Agent": "Mozilla/5.0 (X11; Linux x86_64; rv:122.0) Gecko/20100101 Firefox/122.0",
  "Referer": "https://neal.fun/infinite-craft/",
  "Connection": "keep-alive",
}

def scrape(item1: str, item2: str, tries: int = 0) -> dict[str, str] | None:
    
    params = {
        "first": item1,
        "second": item2,
    }

    try:
        return requests.get(URL, params = params, headers = HEADERS).json()
    except:
        if tries < MAX_TRIES:
            print(f"Failed to retrieve {item1} + {item2}. Retry attempt: {tries + 1}")
            return scrape(item1, item2, tries + 1)

if __name__ == "__main__":
    print(scrape("Fire", "Water"))