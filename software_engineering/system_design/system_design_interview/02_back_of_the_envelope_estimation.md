# CHAPTER 2: BACK-OF-THE-ENVELOPE ESTIMATION

- [CHAPTER 2: BACK-OF-THE-ENVELOPE ESTIMATION](#chapter-2-back-of-the-envelope-estimation)
  - [Power of two](#power-of-two)
  - [Latency numbers every programmer should know](#latency-numbers-every-programmer-should-know)
  - [Availability numbers](#availability-numbers)
  - [Example: Estimate Twitter QPS and storage requirements](#example-estimate-twitter-qps-and-storage-requirements)
  - [Tips](#tips)

According to Jeff Dean: `back-of-the-envelope` calculations are estimates you
create using a combination of thought experiments and common performance
numbers to get a good feel for which designs will meet your requirements.

The following concepts should be well understood:

- power of two
- latency numbers every programmer should know
- availability numbers

## Power of two

The data volume unit uses the power of 2.

| Power | Approximate value | Full name  | Short name |
| ----- | ----------------- | ---------- | ---------- |
| 10    | 1 Thousand        | 1 Kilobyte | 1 KB       |
| 20    | 1 Million         | 1 Megabyte | 1 MB       |
| 30    | 1 Billion         | 1 Gigabyte | 1 GB       |
| 40    | 1 Trillion        | 1 Terabyte | 1 TB       |
| 50    | 1 Quadrillion     | 1 Petabyte | 1 PB       |

## Latency numbers every programmer should know

> - <https://highscalability.com/google-pro-tip-use-back-of-the-envelope-calculations-to-choo/>
> - <https://colin-scott.github.io/personal_website/research/interactive_latency.html>

- Memory is fast but the disk is slow.
- Avoid disk seeks if possible.
- Simple compression algorithms are fast.
- Compress data before sending it over the internet if possible.
- Data centers are usually in different regions, and it takes time to send data
  between them.

## Availability numbers

High availability is measured as a percentage, with 100% means a service that
has 0 downtime. Most services fall between 99% and 100%.

A ***service level agreement (SLA)*** is an agreement between you (the service
provider) and your customer, and this agreement formally defines the level of
uptime your service will deliver. Most cloud providers Amazon, Google, and
Microsoft set their SLAs at `99.9%` or above. Uptime is traditionally measured
in nines. The more the nines, the better.

| Availability % | Downtime per day    | Downtime per year |
| -------------- | ------------------- | ----------------- |
| 99%            | 14.40 minutes       | 3.65 days         |
| 99.9%          | 1.44 minutes        | 8.77 hours        |
| 99.99%         | 8.64 seconds        | 52.60 minutes     |
| 99.999%        | 864.00 milliseconds | 5.26 minutes      |
| 99.9999%       | 86.40 milliseconds  | 31.56 seconds     |

## Example: Estimate Twitter QPS and storage requirements

**Assumptions**:

- 300 million monthly active users.
- 50% of users use Twitter daily.
- Users post 2 tweets per day on average.
- 10% of tweets contain media.
- Data is stored for 5 years.

**Estimations**:

Query per second (QPS) estimate:

- Daily active users (DAU) = `300 million * 50% = 150 million`
- Tweets QPS = `150 million * 2 tweets / 24 hour / 3600 seconds = ~3500`
- Peek QPS = `2 * QPS = ~7000`

We will only estimate media storage here.

- Average tweet size:
  - `tweet_id` 64 bytes
  - `text` 140 bytes
  - `media` 1MB
- Media storage: `150 million * 2 * 10% * 1MB = 30 TB per day`
- 5-year media storage: `30 TB * 365 * 5 = ~55PB`

## Tips

Back-of-the-envelope estimation is all about the process. Solving the problem
is more important than obtaining results. Here are a few tips to follow:

- Rounding and Approximation. It is difficult to perform complicated math
  operations during the interview. For example, what is the result of
  `99987 / 9.1`? Precision is not expected. Use round numbers and approximation
  to your advantage. The division question can be simplified as follows:
  `100,000 / 10`.
- Write down your assumptions. It is a good idea to write down your assumptions
  to be referenced later.
- Label your units. When you write down “5”, does it mean 5 KB or 5 MB? You
  might confuse yourself with this. Write down the units because “5 MB” helps
  to remove ambiguity.
- Commonly asked back-of-the-envelope estimations:
  - QPS
  - peak QPS
  - storage
  - cache
  - number of servers
  - ...
